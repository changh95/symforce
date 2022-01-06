from __future__ import annotations

import dataclasses
from dataclasses import dataclass

from lcmtypes.sym._optimization_iteration_t import optimization_iteration_t
from lcmtypes.sym._optimizer_params_t import optimizer_params_t

from symforce import typing as T
from symforce.opt.factor import Factor
from symforce.values import Values
from symforce import cc_sym


class Optimizer:
    """
    A nonlinear least-squares optimizer

    Typical usage is to construct an Optimizer from a set of factors and keys to optimize, and then
    call `optimize` repeatedly with a `Values`.

    Example creation with an `OptimizationProblem`:

        problem = OptimizationProblem(subproblems=[...], residual_blocks=...)
        factors = problem.make_factors("my_problem")
        optimized_keys = set(problem.optimized_keys())

        optimizer = Optimizer(factors, optimized_keys)

    Example creation with a single `Factor`:

        factor = Factor([my_key_0, my_key_1, my_key_2], my_residual_function)

        optimizer = Optimizer(
            factors=[factor],
            optimized_keys={my_key_0, my_key_1},
        )

    And usage:

        initial_guess = Values(...)
        result = optimizer.optimize(initial_guess)
        print(result.optimized_values)

    Wraps the C++ `sym::Optimizer` class in `opt/optimizer.h`, so the API is mostly the same and
    optimization results will be identical.

    Args:
        factors: A sequence of Factor objects representing the residuals in the problem
        optimized_keys: A set of the keys to be optimized
        params: Params for the optimizer
    """

    @dataclass
    class Params:
        """
        Parameters for the Python Optimizer

        Mirrors the optimizer_params_t LCM type, see documentation there for information on each
        parameter
        """

        verbose: bool = True
        initial_lambda: float = 1.0
        lambda_up_factor: float = 4.0
        lambda_down_factor: float = 1 / 4.0
        lambda_lower_bound: float = 0.0
        lambda_upper_bound: float = 1000000.0
        use_diagonal_damping: bool = False
        use_unit_damping: bool = True
        keep_max_diagonal_damping: bool = False
        diagonal_damping_min: float = 1e-6
        iterations: int = 50
        early_exit_min_reduction: float = 1e-6
        enable_bold_updates: bool = False

    @dataclass
    class Result:
        """
        The result of an optimization, with additional stats and debug information

        initial_values:
            The initial guess used for this optimization

        optimized_values:
            The best Values achieved during the optimization (Values with the smallest error)

        iteration_stats:
            Per-iteration stats, if requested, like the error per iteration.  If debug stats are
            turned on, also the Values and linearization per iteration.

        early_exited:
            Did the optimization early exit?  This can happen because it converged successfully,
            of because it was unable to make progress

        best_index:
            The index into iteration_stats for the iteration that produced the smallest error.  I.e.
            `result.iteration_stats[best_index].values == optimized_values`.  This is not guaranteed
            to be the last iteration, if the optimizer tried additional steps which did not reduce
            the error
        """

        initial_values: Values
        optimized_values: Values
        iteration_stats: T.Sequence[optimization_iteration_t]
        early_exited: bool
        best_index: int

        def error(self) -> float:
            return self.iteration_stats[self.best_index].new_error

    def __init__(
        self, factors: T.Sequence[Factor], optimized_keys: T.Set[str], params: Optimizer.Params
    ):
        self.factors = factors
        self.optimized_keys = optimized_keys
        self.params = params

        self._initialized = False

        # Initialize the keys map with the optimized keys, which are needed to construct the factors
        # This works because the factors maintain a reference to this, so everything is fine as long
        # as the unoptimized keys are also in here before we attempt to linearize any of the factors
        self._cc_keys_map = {key: cc_sym.Key("x", i) for i, key in enumerate(optimized_keys)}

        self._cc_optimizer = cc_sym.Optimizer(
            optimizer_params_t(**dataclasses.asdict(self.params)),
            [factor.cc_factor(self.optimized_keys, self._cc_keys_map) for factor in self.factors],
        )

    def _initialize(self, values: Values) -> None:
        # Add unoptimized keys into the keys map
        for i, key in enumerate(values.keys_recursive()):
            if key not in self._cc_keys_map:
                # Give these a different name (`v`) so we don't have to deal with numbering
                self._cc_keys_map[key] = cc_sym.Key("v", i)

        self._initialized = True

    def optimize(self, initial_guess: Values) -> Optimizer.Result:
        """
        Optimize from the given initial guess, and return the optimized Values and stats

        Args:
            initial_guess: A Values containing the initial guess, should contain at least all the
                           keys required by the `factors` passed to the constructor

        Returns:
            The optimization results, with additional stats and debug information.  See the
            `Optimizer.Result` documentation for more information
        """
        initial_guess = initial_guess.dataclasses_to_values()

        if not self._initialized:
            self._initialize(initial_guess)

        cc_values = cc_sym.Values()
        for key, cc_key in self._cc_keys_map.items():
            cc_values.set(cc_key, initial_guess[key])

        stats = self._cc_optimizer.optimize(cc_values)

        optimized_values = Values(
            **{key: cc_values.at(self._cc_keys_map[key]) for key in initial_guess.keys_recursive()}
        )

        return Optimizer.Result(
            initial_values=initial_guess,
            optimized_values=optimized_values,
            iteration_stats=stats.iterations,
            best_index=stats.best_index,
            early_exited=stats.early_exited,
        )