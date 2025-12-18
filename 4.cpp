#include <iostream>
#include <vector>
#include <string>
#include <sstream>

class IP {
private:
    unsigned char octets[4];

public:
    IP() : octets{0, 0, 0, 0} {}

    IP(unsigned char o0, unsigned char o1, unsigned char o2, unsigned char o3)
        : octets{o0, o1, o2, o3} {}

    IP(const std::string& ip_str) {
        std::istringstream iss(ip_str);
        std::string token;
        int i = 0;

        while (std::getline(iss, token, '.') && i < 4) {
            int octet = std::stoi(token);
            octets[i++] = static_cast<unsigned char>(octet);
        }
    }

    IP& operator++() {
        for (int i = 3; i >= 0; --i) {
            if (octets[i] < 255) {
                ++octets[i];
                break;
            } else {
                octets[i] = 0;
            }
        }
        return *this;
    }

    bool operator<(const IP& other) const {
        for (int i = 0; i < 4; ++i) {
            if (octets[i] != other.octets[i]) {
                return octets[i] < other.octets[i];
            }
        }
        return false;
    }

    bool operator<=(const IP& other) const {
        return *this < other || *this == other;
    }

    bool operator==(const IP& other) const {
        return octets[0] == other.octets[0] &&
               octets[1] == other.octets[1] &&
               octets[2] == other.octets[2] &&
               octets[3] == other.octets[3];
    }

    friend std::ostream& operator<<(std::ostream& os, const IP& ip) {
        os << static_cast<int>(ip.octets[0]) << "."
           << static_cast<int>(ip.octets[1]) << "."
           << static_cast<int>(ip.octets[2]) << "."
           << static_cast<int>(ip.octets[3]);
        return os;
    }

    friend std::istream& operator>>(std::istream& is, IP& ip) {
        std::string ip_str;
        is >> ip_str;
        ip = IP(ip_str);
        return is;
    }
};

std::vector<IP> get_ip_range(const IP& start, const IP& end) {
    std::vector<IP> ips;
    IP current = start;

    while (current <= end) {
        ips.push_back(current);
        ++current;
    }

    return ips;
}

int main() {
    IP start_ip, end_ip;

    std::cout << "Enter start IP address: ";
    std::cin >> start_ip;

    std::cout << "Enter end IP address: ";
    std::cin >> end_ip;

    std::vector<IP> ip_range = get_ip_range(start_ip, end_ip);

    std::cout << "\nIP addresses in range " << start_ip << " to " << end_ip << ":\n";
    for (const auto& ip : ip_range) {
        std::cout << ip << std::endl;
    }

    return 0;
}
