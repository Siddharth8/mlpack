/**
 * @file dtnn_rules.hpp
 * @author Ryan Curtin
 *
 * A set of rules for the dual-tree k-means algorithm which uses dual-tree
 * nearest neighbor search.  For the most part we'll call out to
 * NeighborSearchRules when we can.
 */
#ifndef __MLPACK_METHODS_KMEANS_DTNN_RULES_HPP
#define __MLPACK_METHODS_KMEANS_DTNN_RULES_HPP

#include <mlpack/methods/neighbor_search/neighbor_search.hpp>

namespace mlpack {
namespace kmeans {

template<typename MetricType, typename TreeType>
class DTNNKMeansRules : public neighbor::NeighborSearchRules<
    neighbor::NearestNeighborSort, MetricType, TreeType>
{
 public:
  DTNNKMeansRules(const arma::mat& centroids,
                  const arma::mat& dataset,
                  arma::Mat<size_t>& neighbors,
                  arma::mat& distances,
                  MetricType& metric,
                  const std::vector<bool>& prunedPoints,
                  const std::vector<size_t>& oldFromNewCentroids);

  double BaseCase(const size_t queryIndex, const size_t referenceIndex);

  double Score(const size_t queryIndex, TreeType& referenceNode);
  double Score(TreeType& queryNode, TreeType& referenceNode);
  double Rescore(const size_t queryIndex,
                 TreeType& referenceNode,
                 const double oldScore);
  double Rescore(TreeType& queryNode,
                 TreeType& referenceNode,
                 const double oldScore);

 private:

  const std::vector<bool>& prunedPoints;

  const std::vector<size_t>& oldFromNewCentroids;
};

} // namespace kmeans
} // namespace mlpack

#include "dtnn_rules_impl.hpp"

#endif