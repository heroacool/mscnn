// ------------------------------------------------------------------
// MS-CNN
// Copyright (c) 2016 The Regents of the University of California
// see mscnn/LICENSE for details
// Written by Zhaowei Cai [zwcai-at-ucsd.edu]
// Please email me if you find bugs, or have suggestions or questions!
// ------------------------------------------------------------------

#ifndef CAFFE_BOX_OUTPUT_LAYERS_HPP_
#define CAFFE_BOX_OUTPUT_LAYERS_HPP_

#include <vector>

#include "caffe/blob.hpp"
#include "caffe/layer.hpp"
#include "caffe/proto/caffe.pb.h"

namespace caffe {

template <typename Dtype>
class BoxOutputLayer : public Layer<Dtype> {
 public:
  explicit BoxOutputLayer(const LayerParameter& param)
      : Layer<Dtype>(param) {}
  virtual void LayerSetUp(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  virtual void Reshape(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);

  virtual inline const char* type() const { return "BoxOutput"; }

  virtual inline int MinBottomBlobs() const { return 1; }
  virtual inline int MinTopBlobs() const { return 1; }
  virtual inline int MaxTopBlobs() const { return 2; }

 protected:
  virtual void Forward_cpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);
  /*virtual void Forward_gpu(const vector<Blob<Dtype>*>& bottom,
      const vector<Blob<Dtype>*>& top);*/
  virtual void Backward_cpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom){
    for (int i = 0; i < propagate_down.size(); ++i) {
      if (propagate_down[i]) { NOT_IMPLEMENTED; }
    }
  }
  /*virtual void Backward_gpu(const vector<Blob<Dtype>*>& top,
      const vector<bool>& propagate_down, const vector<Blob<Dtype>*>& bottom){
    for (int i = 0; i < propagate_down.size(); ++i) {
      if (propagate_down[i]) { NOT_IMPLEMENTED; }
    }
  }*/
  
  //shared_ptr<Caffe::RNG> shuffle_rng_;
  float fg_thr_;
  float iou_thr_;
  string nms_type_;
  bool output_proposal_with_score_;
};

}  // namespace caffe

#endif  // CAFFE_BOX_OUTPUT_LAYERS_HPP_
