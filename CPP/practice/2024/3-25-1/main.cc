/*
 * @Author: ls02 liangson02@163.com
 * @Date: 2024-03-25 14:26:51
 * @LastEditors: ls02 liangson02@163.com
 * @LastEditTime: 2024-03-27 09:57:42
 * @FilePath: /2024/3-25-1/main.cc
 * @Description: 这是默认设置,请设置`customMade`, 打开koroFileHeader查看配置
 * 进行设置: https://github.com/OBKoro1/koro1FileHeader/wiki/%E9%85%8D%E7%BD%AE
 */
#include <yaml-cpp/yaml.h>

#include <bitset>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

class CIDR {
   public:
    CIDR(const std::string& ip_or_cidr) {
        size_t pos = ip_or_cidr.find('/');
        std::string ip = ip_or_cidr;
        int subnet_size = 32;  // 默认为单个 IP 地址

        if (pos != std::string::npos) {
            ip = ip_or_cidr.substr(0, pos);
            subnet_size = std::stoi(ip_or_cidr.substr(pos + 1));
        }

        _base_address = IpToUInt(ip);
        // 取反得到32个比特位为1
        _subnet_mask = ~((1ULL << (32 - subnet_size)) - 1);
        _network_address = _base_address & _subnet_mask;
    }
    bool CheckIPExistence(const std::string& ip) const {
        uint32_t addr = IpToUInt(ip);

        return _base_address == addr;
    }

    bool Contains(const std::string& ip) const {
        uint32_t addr = IpToUInt(ip);
        return (addr & _subnet_mask) == _network_address;
    }

   private:
    uint32_t _base_address = 0;
    uint32_t _subnet_mask = 0;
    uint32_t _network_address = 0;

    static uint32_t IpToUInt(const std::string& ip) {
        int a, b, c, d;
        sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
        return (a << 24) | (b << 16) | (c << 8) | d;
    }
};

class AccessControl {
   public:
    enum class RuleType { Allow, Deny };

    AccessControl(const std::string& config_path) : _config_path(config_path) {
        LoadConfig(_config_path);
    }

    AccessControl() {}

    void LoadConfig(const std::string& config_path) {
        YAML::Node config = YAML::LoadFile(config_path);
        if (config) {
            for (const auto& cidr : config["WhiteList"]) {
                _rules.push_back(Rule(cidr.as<std::string>(), RuleType::Allow));
            }

            for (const auto& cidr : config["BlackList"]) {
                _rules.push_back(Rule(cidr.as<std::string>(), RuleType::Deny));
            }
        } else {
            std::cout << "Failed to load config file" << std::endl;
        }
    }

    bool AddRule(const std::string& cidr, RuleType type,
                 bool save_to_file = true) {
        if (save_to_file) {
            YAML::Node config = YAML::LoadFile(_config_path);
            std::list<std::string> white_list;
            std::list<std::string> black_list;

            if (config["WhiteList"]) {
                white_list = config["WhiteList"].as<std::list<std::string>>();
            }

            if (config["BlackList"]) {
                black_list = config["BlackList"].as<std::list<std::string>>();
            }
        }

        // 检查 ip 是否已在名单里面
        for (auto e : _rules) {
            if (e.cidr.CheckIPExistence(cidr)) {
                return false;
            }
        }

        _rules.push_back(Rule(cidr, type));

        if (save_to_file) {
            // 如果不在里面，我们需要进行添加
            if (type == RuleType::Allow) {
                white_list.push_back(cidr);
            } else {
                black_list.push_back(cidr);
            }

            if (config["WhiteList"]) {
                config["WhiteList"] = white_list;
            }

            if (config["BlackList"]) {
                config["BlackList"] = black_list;
            }

            std::ofstream fout(_config_path);
            fout << config;
        }

        return true;
    }

    bool IsAllowed(const std::string& ip) const {
        bool allowed = false;

        for (const auto& rule : _rules) {
            if (rule.cidr.Contains(ip)) {
                // 默认黑名单优先
                if (rule.type == RuleType::Deny) {
                    return false;  // 遇到明确的拒绝规则，立即拒绝
                } else if (rule.type == RuleType::Allow) {
                    allowed = true;  // 记录找到允许规则
                    // 不直接返回，以便检查是否有后续的拒绝规则
                }
            }
        }

        if (ip == "127.0.0.1") {
            allowed = true;
        }

        return allowed;  // 如果没有明确的拒绝规则，根据是否找到允许规则决定
    }

   private:
    struct Rule {
        CIDR cidr;
        RuleType type;

        Rule(const std::string& cidrString, RuleType ruleType)
            : cidr(cidrString), type(ruleType) {}
    };

   private:
    std::string _config_path = "/opt/sudis/access_control.yaml";

    std::list<Rule> _rules;
};

int main() {
    // std::string str = "../access_control.yaml";
    std::string str =
        "/home/ls/code/Linux_Code/CPP/practice/2024/3-25-1/access_control.yaml";
    AccessControl acl(str);
    acl.AddRule("192.168.1.151", AccessControl::RuleType::Deny);
    acl.AddRule("192.168.1.163", AccessControl::RuleType::Allow);

    std::cout << "192.168.1.50: "
              << (acl.IsAllowed("192.168.1.50") ? "Allowed" : "Denied")
              << std::endl;
    std::cout << "192.168.1.100: "
              << (acl.IsAllowed("192.168.1.100") ? "Allowed" : "Denied")
              << std::endl;
    std::cout << "192.168.1.151: "
              << (acl.IsAllowed("192.168.1.151") ? "Allowed" : "Denied")
              << std::endl;

    std::cout << "192.168.1.163: "
              << (acl.IsAllowed("192.168.1.163") ? "Allowed" : "Denied")
              << std::endl;

    return 0;
}
