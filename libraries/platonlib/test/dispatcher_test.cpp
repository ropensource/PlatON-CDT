#include "platon/dispatcher.hpp"
#include "platon/common.h"
#include <string>
#include <iostream>
#include <vector>

using namespace platon;
std::vector<byte> result;

#ifdef __cplusplus
extern "C" {
#endif

void platon_return(const void *res, const size_t len){
    byte *ptr = (byte *)res;
    std::vector<byte> my_return;
    for(size_t i = 0; i < len; i++) {
        my_return.push_back(*ptr);
        ptr++;
    }
    std::string str_return;
    fetch(RLP(my_return), str_return);
    std::cout << str_return << std::endl;
}

size_t platon_input_length(void){
    return result.size();
}

void platon_get_input(const void *inputptr){
    byte *ptr = (byte *)inputptr;
    for (auto one :result) {
        *ptr = one;
        ptr++;
    }
}
void platon_panic( const char* cstr, const uint32_t len){
    for (uint32_t i = 0; i < len; i++) {
        std::cout << *cstr;
        cstr++;
    }
    std::cout << std::endl;
}

#ifdef __cplusplus
}
#endif


class hello {
    public:
        hello(){m_info["jatel"] = "jatel_info";}
        void init(){}

        int set_message(const std::string &name, const std::string &one_message){
            m_info[name] = one_message;
            return 0;
        }

        int change_message(const std::string &name, const std::string  &one_message){
            m_info[name] = one_message;
            return 0;
        }

        int delete_message(const std::string &name){
            m_info.erase(name);
            return 0;
        }

        std::string get_message(const std::string &name){
            return m_info[name];
        }
    private:
        std::map<std::string, std::string> m_info; 
};

PLATON_DISPATCH(hello, (init)(set_message)(change_message)(delete_message)(get_message))

int main(int argc, char **argv) {
    RLPStream wht_stream;
    wht_stream.appendList(2) << "get_message" << "jatel";
    result = wht_stream.out();
    invoke();
}