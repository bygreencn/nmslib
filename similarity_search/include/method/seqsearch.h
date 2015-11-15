/**
 * Non-metric Space Library
 *
 * Authors: Bilegsaikhan Naidan (https://github.com/bileg), Leonid Boytsov (http://boytsov.info).
 * With contributions from Lawrence Cayton (http://lcayton.com/) and others.
 *
 * For the complete list of contributors and further details see:
 * https://github.com/searchivarius/NonMetricSpaceLib 
 * 
 * Copyright (c) 2014
 *
 * This code is released under the
 * Apache License Version 2.0 http://www.apache.org/licenses/.
 *
 */
#ifndef _SEQSEARCH_H_
#define _SEQSEARCH_H_

#include <string>

#include "index.h"

#define METH_SEQ_SEARCH             "seq_search"

namespace similarity {

using std::string;
using std::vector;

// Sequential search

template <typename dist_t>
class SeqSearch : public Index<dist_t> {
 public:
  SeqSearch(Space<dist_t>& space, const ObjectVector& data);
  void CreateIndex(const AnyParams& );
  virtual ~SeqSearch();

  const std::string StrDesc() const { return "Sequential search"; }

  void Search(RangeQuery<dist_t>* query, IdType) const;
  void Search(KNNQuery<dist_t>* query, IdType) const;

  void SetQueryTimeParams(const AnyParams& params){}
 private:
  Space<dist_t>&          space_;
  const ObjectVector&     origData_;
  char*                   cacheOptimizedBucket_;

  ObjectVector*           pData_;
  bool                    multiThread_;
  IdTypeUnsign            threadQty_;
  vector<ObjectVector>    vvThreadData;

  const ObjectVector& getData() const { return pData_ != NULL ? *pData_ : origData_; }
  // disable copy and assign
  DISABLE_COPY_AND_ASSIGN(SeqSearch);
};

}   // namespace similarity

#endif     // _SEQSEARCH_H_
