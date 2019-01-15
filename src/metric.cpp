//
// Created by leleyu on 19-1-15.
//


#include <graph/metric.h>

namespace graph {
namespace metric {
using namespace torch;

double precision_score(Tensor y_pred, Tensor y_true) {
  auto y = y_pred.argmax(1).to(TensorOptions().dtype(kInt64));
  int n_right = torch::eq(y, y_true).sum().item().toInt();
  int n_total = y_pred.size(0);
  return n_right * 1.0 / n_total;
}
} // metrix
} // graph
