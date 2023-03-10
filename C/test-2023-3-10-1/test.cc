#include <iostream>
#include <string>
#include <jsoncpp/json/json.h>

typedef struct request
{
    int x;
    int y;
    char op;
}request;

void Test1()
{
    request req = { 10, 20, '*' };
    Json::Value root;
    root["datax"] = req.x;
    root["datay"] = req.y;
    root["dataop"] = req.op;

    //Json::StyledWriter write;
    Json::FastWriter write;
    std::string json_string = write.write(root);

    std::cout << json_string << std::endl;
}

void Test2()
{
    std::string json_string = R"({"datax":10,"datay":20,"operator":42})";
    Json::Reader reader;
    Json::Value root;

    reader.parse(json_string, root);

    request req;
    req.x = root["datax"].asInt();
    req.y = root["datay"].asInt();
    req.op = (char)root["operator"].asInt();

    std::cout << req.x << " " << req.op << " " << req.y << std::endl;
}

int main(void)
{
    //Test1();
    Test2();
    
    return 0;
}
