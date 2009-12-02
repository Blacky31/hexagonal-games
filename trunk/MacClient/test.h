/*
 *  test.h
 *  Game
 *
 *  Created by Viktor Zhuravel on 12/2/09.
 *  Copyright 2009 Kring. All rights reserved.
 *
 */

#include "AlphaBetaPruningEvaluator.h"
#include "NativeEvaluator.h"
#include "BoardGeometry.h"
#include "CacheStrategy.h"
#include "SquareReversiPosition.h"

typedef game::engine::alpha_beta_pruning_evaluator<
            game::square_reversi::SquareReversiPosition, 
            game::engine::native_evaluator,
            game::engine::boostpool_cache_strategy >
        SquareReversiEvaluator;