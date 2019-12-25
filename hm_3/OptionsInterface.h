#pragma once
#include <string>

namespace Options {
class Options {
 public:
    Options();

    void setDefault();

    void open();

 private:
    void drawOptions();

    int x, y;

    const std::string& info1 = "To change Press '<-' or '->'";
    const std::string& info2 = "To exit, press 'ESC'";

    int selected_id = 0;
};
}  // namespace Options