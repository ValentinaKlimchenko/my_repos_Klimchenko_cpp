#include <iostream>
#include <string>
#include <chrono>
#include <iomanip>
#include <vector>
#include <source_location>

class Tracer {
private:
    std::string message;
    std::chrono::steady_clock::time_point start_time;
    std::source_location location;
    static std::vector<std::string> call_stack;

public:
    Tracer(const std::string& msg = "", std::source_location loc = std::source_location::current())
        : message(msg), location(loc), start_time(std::chrono::steady_clock::now()) {

        call_stack.push_back(location.function_name());
        log("ENTER: " + message);
    }

    ~Tracer() {
        auto end_time = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);

        log("EXIT: " + message + " [took " + std::to_string(duration.count()) + "μs]");

        if (!call_stack.empty()) {
            call_stack.pop_back();
        }
    }

    void log(const std::string& msg) {
        auto now = std::chrono::system_clock::now();
        auto time_t = std::chrono::system_clock::to_time_t(now);
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch()) % 1000;

        std::cout << "[" << std::put_time(std::localtime(&time_t), "%H:%M:%S")
                  << "." << std::setfill('0') << std::setw(3) << ms.count() << "] "
                  << msg << std::endl;
    }

    static void print_call_stack() {
        if (call_stack.empty()) {
            std::cout << "Call stack is empty" << std::endl;
            return;
        }

        for (int i = call_stack.size() - 1; i >= 0; --i) {
            std::cout << call_stack[i] << std::endl;
        }
    }
};

std::vector<std::string> Tracer::call_stack;
