/*
 *  TestEngine.cpp
 *  iPhoneGame
 *
 *  Created by svp on 09.02.10.
 *  Copyright 2010 __MyCompanyName__. All rights reserved.
 *
 */

#include "TestEngine.h"

#include "SquareReversiPosition.h"
#include "SimpleCacheStrategyHelper.h"
#include "AlphaBetaPruningEvaluator.h"
#include "MonteCarloEvaluator.h"
#include "BoardGeometry.h"
#include "GameBoard.h"
#include "NativeEvaluator.h"
#include "CacheStrategy.h"
#include "CacheStrategyHelper_AllTransformsInCache.h"
#include "CacheStrategyHelper_OneTransformInCache.h"


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

// !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

/*
typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::boostpool_cache_strategy,
game::engine::simple_cache_strategy_helper,
false>
SquareReversiEvaluator1_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::stdnew_cache_strategy,
game::engine::simple_cache_strategy_helper,
false>
SquareReversiEvaluator2_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::no_cache_strategy,
game::engine::simple_cache_strategy_helper,
false>
SquareReversiEvaluator3_monte_carlo;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::boostpool_cache_strategy,
game::engine::cache_strategy_helper_all_transfroms_in_cache,
false>
SquareReversiEvaluator21_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::stdnew_cache_strategy,
game::engine::cache_strategy_helper_all_transfroms_in_cache,
false>
SquareReversiEvaluator22_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::no_cache_strategy,
game::engine::cache_strategy_helper_all_transfroms_in_cache,
false>
SquareReversiEvaluator23_monte_carlo;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::boostpool_cache_strategy,
game::engine::cache_strategy_helper_one_transfrom_in_cache,
false>
SquareReversiEvaluator31_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::stdnew_cache_strategy,
game::engine::cache_strategy_helper_one_transfrom_in_cache,
false>
SquareReversiEvaluator32_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::no_cache_strategy,
game::engine::cache_strategy_helper_one_transfrom_in_cache,
false>
SquareReversiEvaluator33_monte_carlo;        


//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::boostpool_cache_strategy,
game::engine::simple_cache_strategy_helper,
true>
SquareReversiEvaluator1_s_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::stdnew_cache_strategy,
game::engine::simple_cache_strategy_helper,
true>
SquareReversiEvaluator2_s_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::no_cache_strategy,
game::engine::simple_cache_strategy_helper,
true>
SquareReversiEvaluator3_s_monte_carlo;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::boostpool_cache_strategy,
game::engine::cache_strategy_helper_all_transfroms_in_cache,
true>
SquareReversiEvaluator21_s_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::stdnew_cache_strategy,
game::engine::cache_strategy_helper_all_transfroms_in_cache,
true>
SquareReversiEvaluator22_s_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::no_cache_strategy,
game::engine::cache_strategy_helper_all_transfroms_in_cache,
true>
SquareReversiEvaluator23_s_monte_carlo;        

// ---------------------------------

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::boostpool_cache_strategy,
game::engine::cache_strategy_helper_one_transfrom_in_cache,
true>
SquareReversiEvaluator31_s_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::stdnew_cache_strategy,
game::engine::cache_strategy_helper_one_transfrom_in_cache,
true>
SquareReversiEvaluator32_s_monte_carlo;

typedef game::engine::alpha_beta_pruning_evaluator<
game::square_reversi::SquareReversiPosition, 
game::engine::monte_carlo_evaluator,
game::engine::no_cache_strategy,
game::engine::cache_strategy_helper_one_transfrom_in_cache,
true>
SquareReversiEvaluator33_s_monte_carlo;        
*/

void test()
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
	
	SquareReversiEvaluator1_s e1_s;
	SquareReversiEvaluator2_s e2_s;
	SquareReversiEvaluator3_s e3_s;
	
	SquareReversiEvaluator21_s e21_s;
	SquareReversiEvaluator22_s e22_s;
	SquareReversiEvaluator23_s e23_s;
	
	SquareReversiEvaluator31_s e31_s;
	SquareReversiEvaluator32_s e32_s;
	SquareReversiEvaluator33_s e33_s;	
/*	
	SquareReversiEvaluator1_monte_carlo e1_monte_carlo;
	SquareReversiEvaluator2_monte_carlo e2_monte_carlo;
	SquareReversiEvaluator3_monte_carlo e3_monte_carlo;
	
	SquareReversiEvaluator21_monte_carlo e21_monte_carlo;
	SquareReversiEvaluator22_monte_carlo e22_monte_carlo;
	SquareReversiEvaluator23_monte_carlo e23_monte_carlo;
	
	SquareReversiEvaluator31_monte_carlo e31_monte_carlo;
	SquareReversiEvaluator32_monte_carlo e32_monte_carlo;
	SquareReversiEvaluator33_monte_carlo e33_monte_carlo;
	
	SquareReversiEvaluator1_s_monte_carlo e1_s_monte_carlo;
	SquareReversiEvaluator2_s_monte_carlo e2_s_monte_carlo;
	SquareReversiEvaluator3_s_monte_carlo e3_s_monte_carlo;
	
	SquareReversiEvaluator21_s_monte_carlo e21_s_monte_carlo;
	SquareReversiEvaluator22_s_monte_carlo e22_s_monte_carlo;
	SquareReversiEvaluator23_s_monte_carlo e23_s_monte_carlo;
	
	SquareReversiEvaluator31_s_monte_carlo e31_s_monte_carlo;
	SquareReversiEvaluator32_s_monte_carlo e32_s_monte_carlo;
	SquareReversiEvaluator33_s_monte_carlo e33_s_monte_carlo;
*/	
	
	game::square_reversi::SquareReversiPosition position;
	
	signed int a, b;
	
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
/*	
	e1_monte_carlo.f2(10, position, a, b);
	e2_monte_carlo.f2(10, position, a, b);
	e3_monte_carlo.f2(10, position, a, b);
	
	e21_monte_carlo.f2(10, position, a, b);
	e22_monte_carlo.f2(10, position, a, b);
	e23_monte_carlo.f2(10, position, a, b);
	
	e31_monte_carlo.f2(10, position, a, b);
	e32_monte_carlo.f2(10, position, a, b);
	e33_monte_carlo.f2(10, position, a, b);
	
	e1_s_monte_carlo.f2(10, position, a, b);
	e2_s_monte_carlo.f2(10, position, a, b);
	e3_s_monte_carlo.f2(10, position, a, b);
	
	e21_s_monte_carlo.f2(10, position, a, b);
	e22_s_monte_carlo.f2(10, position, a, b);
	e23_s_monte_carlo.f2(10, position, a, b);
	
	e31_s_monte_carlo.f2(10, position, a, b);
	e32_s_monte_carlo.f2(10, position, a, b);
	e33_s_monte_carlo.f2(10, position, a, b);
*/ 
}

