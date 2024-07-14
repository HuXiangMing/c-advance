// MIT 许可协议 (MIT)
//
// 版权所有 (c) 2019 Luigi Pertoldi
//
// 特此免费授予任何获得本软件及相关文档文件（“软件”）副本的人
// 处理本软件的权限，包括但不限于使用、复制、修改、合并、出版、分发、再许可和/或销售
// 软件的副本，以及允许软件提供者这样做，但须符合以下条件：
//
// 上述版权声明和本许可声明应包含在本软件的所有副本或重要部分中。
//
// 本软件按“原样”提供，不附带任何明示或暗示的担保，包括但不限于
// 适销性、适用于特定目的和非侵权性的担保。在任何情况下，作者或版权持有人不对因本软件或
// 使用或其他交易中的任何索赔、损害或其他责任承担任何责任，无论是在合同诉讼中、侵权诉讼中
// 还是其他诉讼中。
//
// ============================================================================
//  ___   ___   ___   __    ___   ____  __   __   ___    __    ___
// | |_) | |_) / / \ / /`_ | |_) | |_  ( (` ( (` | |_)  / /\  | |_)
// |_|   |_| \ \_\_/ \_\_/ |_| \ |_|__ _)_) _)_) |_|_) /_/--\ |_| \_
//
// 用于 C++ 循环的非常简单的进度条，带有内部运行变量
//
// 作者：Luigi Pertoldi
// 创建时间：2016 年 12 月 3 日
//
// 注意：当 for 循环中没有其他可能的输出源时，必须使用此进度条
//

#ifndef __PROGRESSBAR_HPP
#define __PROGRESSBAR_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <stdexcept>

class progressbar {

public:
    // 默认析构函数
    ~progressbar() = default;

    // 删除其他所有内容
    progressbar(progressbar const&) = delete;
    progressbar& operator=(progressbar const&) = delete;
    progressbar(progressbar&&) = delete;
    progressbar& operator=(progressbar&&) = delete;

    // 默认构造函数，必须稍后调用 set_niter
    inline progressbar();
    inline progressbar(int n, bool showbar = true, std::ostream& out = std::cerr);

    // 重置进度条以再次使用
    inline void reset();
    // 设置循环迭代次数
    inline void set_niter(int iter);
    // 选择样式
    inline void set_done_char(const std::string& sym) { done_char = sym; }
    inline void set_todo_char(const std::string& sym) { todo_char = sym; }
    inline void set_opening_bracket_char(const std::string& sym) { opening_bracket_char = sym; }
    inline void set_closing_bracket_char(const std::string& sym) { closing_bracket_char = sym; }
    // 仅显示百分比
    inline void show_bar(bool flag = true) { do_show_bar = flag; }
    // 设置输出流
    inline void set_output_stream(const std::ostream& stream) { output.rdbuf(stream.rdbuf()); }
    // 主要功能
    inline void update();

private:
    int progress;
    int n_cycles;
    int last_perc;
    bool do_show_bar;
    bool update_is_called;

    std::string done_char;
    std::string todo_char;
    std::string opening_bracket_char;
    std::string closing_bracket_char;

    std::ostream& output;
};

inline progressbar::progressbar() :
    progress(0),
    n_cycles(0),
    last_perc(0),
    do_show_bar(true),
    update_is_called(false),
    done_char("#"),
    todo_char(" "),
    opening_bracket_char("["),
    closing_bracket_char("]"),
    output(std::cerr) {}

inline progressbar::progressbar(int n, bool showbar, std::ostream& out) :
    progress(0),
    n_cycles(n),
    last_perc(0),
    do_show_bar(showbar),
    update_is_called(false),
    done_char("#"),
    todo_char(" "),
    opening_bracket_char("["),
    closing_bracket_char("]"),
    output(out) {}

inline void progressbar::reset() {
    progress = 0,
        update_is_called = false;
    last_perc = 0;
    return;
}

inline void progressbar::set_niter(int niter) {
    if (niter <= 0) throw std::invalid_argument(
        "progressbar::set_niter: 迭代次数为零或负数");
    n_cycles = niter;
    return;
}

inline void progressbar::update() {

    if (n_cycles == 0) throw std::runtime_error(
        "progressbar::update: 未设置循环次数");

    if (!update_is_called) {
        if (do_show_bar == true) {
            output << opening_bracket_char;
            for (int _ = 0; _ < 50; _++) output << todo_char;
            output << closing_bracket_char << " 0%";
        }
        else output << "0%";
    }
    update_is_called = true;

    int perc = 0;

    // 计算百分比，如果没有变化，则不做任何操作并返回
    perc = progress * 100. / (n_cycles - 1);
    if (perc < last_perc) return;

    // 每单位更新百分比
    if (perc == last_perc + 1) {
        // 擦除正确数量的字符
        if (perc <= 10)                output << "\b\b" << perc << '%';
        else if (perc > 10 and perc < 100) output << "\b\b\b" << perc << '%';
        else if (perc == 100)               output << "\b\b\b" << perc << '%';
    }
    if (do_show_bar == true) {
        // 每十个单位更新进度条
        if (perc % 2 == 0) {
            // 擦除右括号
            output << std::string(closing_bracket_char.size(), '\b');
            // 擦除尾随百分比字符
            if (perc < 10)               output << "\b\b\b";
            else if (perc >= 10 && perc < 100) output << "\b\b\b\b";
            else if (perc == 100)              output << "\b\b\b\b\b";

            // 擦除 'todo_char'
            for (int j = 0; j < 50 - (perc - 1) / 2; ++j) {
                output << std::string(todo_char.size(), '\b');
            }

            // 添加一个额外的 'done_char'
            if (perc == 0) output << todo_char;
            else           output << done_char;

            // 用 'todo_char' 填充
            for (int j = 0; j < 50 - (perc - 1) / 2 - 1; ++j) output << todo_char;

            // 重新添加尾随百分比字符
            output << closing_bracket_char << ' ' << perc << '%';
        }
    }
    last_perc = perc;
    ++progress;
    output << std::flush;

    return;
}

#endif