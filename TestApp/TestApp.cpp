// TestApp.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream>
#include <iterator>
#include <algorithm>

#include "../Engine/AlphaBetaPruningEvaluator.h"
#include "../Engine/MonteCarloEvaluator.h"
#include "../Engine/BoardGeometry.h"
#include "../Engine/GameBoard.h"
#include "../Engine/NativeEvaluator.h"
#include "../Engine/CacheStrategy.h"
#include "../Engine/SimpleCacheStrategyHelper.h"
#include "../Engine/CacheStrategyHelper_AllTransformsInCache.h"
#include "../Engine/CacheStrategyHelper_OneTransformInCache.h"
#include "../SquareReversiEngine/SquareReversiPosition.h"

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy,
			game::engine::simple_cache_strategy_helper,
			false>
        SquareReversiEvaluator1;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::simple_cache_strategy_helper,
			false>
        SquareReversiEvaluator2;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::simple_cache_strategy_helper,
			false>
        SquareReversiEvaluator3;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache,
			false>
        SquareReversiEvaluator21;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache,
			false>
        SquareReversiEvaluator22;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache,
			false>
        SquareReversiEvaluator23;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache,
			false>
        SquareReversiEvaluator31;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache,
			false>
        SquareReversiEvaluator32;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache,
			false>
        SquareReversiEvaluator33;        


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy,
			game::engine::simple_cache_strategy_helper,
			true>
        SquareReversiEvaluator1_s;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::simple_cache_strategy_helper,
			true>
        SquareReversiEvaluator2_s;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::simple_cache_strategy_helper,
			true>
        SquareReversiEvaluator3_s;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache,
			true>
        SquareReversiEvaluator21_s;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache,
			true>
        SquareReversiEvaluator22_s;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache,
			true>
        SquareReversiEvaluator23_s;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache,
			true>
        SquareReversiEvaluator31_s;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache,
			true>
        SquareReversiEvaluator32_s;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache,
			true>
        SquareReversiEvaluator33_s;        


int _tmain(int argc, _TCHAR* argv[])
{
	SquareReversiEvaluator1 e1;
	SquareReversiEvaluator2 e2;
	SquareReversiEvaluator3 e3;

	SquareReversiEvaluator21 e21;
	SquareReversiEvaluator22 e22;
	SquareReversiEvaluator23 e23;

	SquareReversiEvaluator31 e31;
	SquareReversiEvaluator32 e32;
	SquareReversiEvaluator33 e33;

	SquareReversiEvaluator1 e1_s;
	SquareReversiEvaluator2 e2_s;
	SquareReversiEvaluator3 e3_s;

	SquareReversiEvaluator21 e21_s;
	SquareReversiEvaluator22 e22_s;
	SquareReversiEvaluator23 e23_s;

	SquareReversiEvaluator31 e31_s;
	SquareReversiEvaluator32 e32_s;
	SquareReversiEvaluator33 e33_s;

	game::square_reversi::SquareReversiPosition position;

	signed int a, b, r;

	e1.f2(10, position, a, b);
	e2.f2(10, position, a, b);
	e3.f2(10, position, a, b);

	e21.f2(10, position, a, b);
	e22.f2(10, position, a, b);
	e23.f2(10, position, a, b);

	e31.f2(10, position, a, b);
	e32.f2(10, position, a, b);
	e33.f2(10, position, a, b);

	e1_s.f2(10, position, a, b);
	e2_s.f2(10, position, a, b);
	e3_s.f2(10, position, a, b);

	e21_s.f2(10, position, a, b);
	e22_s.f2(10, position, a, b);
	e23_s.f2(10, position, a, b);

	e31_s.f2(10, position, a, b);
	e32_s.f2(10, position, a, b);
	e33_s.f2(10, position, a, b);

	return 0;
}

