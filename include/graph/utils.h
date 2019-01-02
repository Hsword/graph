//
// Created by leleyu on 2018-12-25.
//

#ifndef TEST_UTILS_H
#define TEST_UTILS_H

#include <torch/torch.h>

namespace graph {
  
  namespace utils {

    torch::data::Example<> parseLibSVM(std::string str);
    
    torch::data::Example<> parseLibSVM(std::string str, size_t n_dim);

  };
};


#endif //TEST_UTILS_H