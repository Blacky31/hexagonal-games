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
			game::engine::simple_cache_strategy_helper>
        SquareReversiEvaluator1;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::simple_cache_strategy_helper>
        SquareReversiEvaluator2;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::simple_cache_strategy_helper>
        SquareReversiEvaluator3;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache>
        SquareReversiEvaluator21;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache>
        SquareReversiEvaluator22;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::cache_strategy_helper_all_transfroms_in_cache>
        SquareReversiEvaluator23;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache>
        SquareReversiEvaluator31;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::stdnew_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache>
        SquareReversiEvaluator32;
        
typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::no_cache_strategy,
			game::engine::cache_strategy_helper_one_transfrom_in_cache>
        SquareReversiEvaluator33;        


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

	return 0;
}

