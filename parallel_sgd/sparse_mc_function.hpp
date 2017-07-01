/**
 * @file sparse_mc_function.hpp
 * @author Shikhar Bhardwaj
 *
 * Implementation of the hinge loss function for training a sparse SVM with the
 * parallel SGD algorithm
 *
 * mlpack is free software; you may redistribute it and/or modify it under the
 * terms of the 3-clause BSD license.  You should have received a copy of the
 * 3-clause BSD license along with mlpack.  If not, see
 * http://www.opensource.org/licenses/BSD-3-Clause for more information.
 */
#ifndef MLPACK_CORE_OPTIMIZERS_PARALLEL_SGD_SPARSE_MC_HPP
#define MLPACK_CORE_OPTIMIZERS_PARALLEL_SGD_SPARSE_MC_HPP
#include <mlpack/prereqs.hpp>

class SparseMCLossFunction{
 public:
  //! Nothing to do for the default constructor.
  SparseMCLossFunction() = default;

  //! Member initialization constructor.
  SparseMCLossFunction(arma::uvec& rows, arma::uvec& cols, arma::vec& ratings,
      size_t rank);

  //! Special Initialization constructor.
  SparseMCLossFunction(arma::sp_mat& dataset, size_t rank);

  //! Evaluate a function.
  double Evaluate(const arma::mat& weights, size_t id);

  //! Evaluate the gradient of a function.
  void Gradient(const arma::mat& weights, size_t id, arma::sp_mat& gradient);

  //! Get the height of the sparse matrix.
  size_t NumRows() const { return numRows; }
  //! Modify the height of the sparse matrix.
  size_t& NumRows() { return numRows; }

  //! Get the width of the sparse matrix.
  size_t NumCols() const { return numCols; }
  //! Modify the width of the sparse matrix.
  size_t& NumCols() { return numCols; }

  //! Get the rank.
  size_t Rank() const { return rank; }
  //! Modify the rank.
  size_t& Rank() { return rank; }

  //! Return the number of functions.
  size_t NumFunctions();

 private:
  void CalculateStatistics();

  //! The training data.
  arma::uvec rows;
  arma::uvec cols;
  arma::vec ratings;

  //! The statistics.
  arma::uvec colCnt;
  arma::uvec rowCnt;
  //! Mean rating.
  double meanRating;

  //! The height of the sparse matrix
  size_t numRows;

  //! The width of the sparse matrix
  size_t numCols;

  //! The width of the first factor.
  size_t rank;
};

// Include implementation
#include "sparse_mc_function_impl.hpp"

#endif
