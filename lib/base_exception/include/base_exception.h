//
// Created by kira on 28.04.2020.
//

#ifndef LIB_BASE_EXCEPTION_INCLUDE_BASE_EXCEPTION_H_
#define LIB_BASE_EXCEPTION_INCLUDE_BASE_EXCEPTION_H_

#include <exception>
#include <string>


namespace exception {
class Exception : public std::exception {
 public:
    explicit Exception(std::string es);

    [[nodiscard]] const char *what() const noexcept override;

 private:
    std::string _errstr;
};
}  // namespace process

#endif //LIB_BASE_EXCEPTION_INCLUDE_BASE_EXCEPTION_H_
