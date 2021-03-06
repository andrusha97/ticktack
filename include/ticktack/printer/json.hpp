#pragma once

#include "ticktack/watcher.hpp"

namespace ticktack {

class suite_t;
class analyzed_t;
class json_printer_t : public watcher_t {
public:
    void
    start();

    void
    suite_start(const std::string& name, const suite_t& suite);

    void
    relative_pass(const std::string& name, const analyzed_t& info_b, const analyzed_t& info);

    void
    pass(const std::string& name, const analyzed_t& info);

    void
    suite_complete(const std::string& suite, long long elapsed);

    void
    complete(long long elapsed);
};

}
