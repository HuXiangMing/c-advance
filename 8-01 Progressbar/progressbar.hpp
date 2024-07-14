// MIT ���Э�� (MIT)
//
// ��Ȩ���� (c) 2019 Luigi Pertoldi
//
// �ش���������κλ�ñ����������ĵ��ļ��������������������
// ���������Ȩ�ޣ�������������ʹ�á����ơ��޸ġ��ϲ������桢�ַ�������ɺ�/������
// ����ĸ������Լ���������ṩ���������������������������
//
// ������Ȩ�����ͱ��������Ӧ�����ڱ���������и�������Ҫ�����С�
//
// ���������ԭ�����ṩ���������κ���ʾ��ʾ�ĵ�����������������
// �����ԡ��������ض�Ŀ�ĺͷ���Ȩ�Եĵ��������κ�����£����߻��Ȩ�����˲����������
// ʹ�û����������е��κ����⡢�𺦻��������γе��κ����Σ��������ں�ͬ�����С���Ȩ������
// �������������С�
//
// ============================================================================
//  ___   ___   ___   __    ___   ____  __   __   ___    __    ___
// | |_) | |_) / / \ / /`_ | |_) | |_  ( (` ( (` | |_)  / /\  | |_)
// |_|   |_| \ \_\_/ \_\_/ |_| \ |_|__ _)_) _)_) |_|_) /_/--\ |_| \_
//
// ���� C++ ѭ���ķǳ��򵥵Ľ������������ڲ����б���
//
// ���ߣ�Luigi Pertoldi
// ����ʱ�䣺2016 �� 12 �� 3 ��
//
// ע�⣺�� for ѭ����û���������ܵ����Դʱ������ʹ�ô˽�����
//

#ifndef __PROGRESSBAR_HPP
#define __PROGRESSBAR_HPP

#include <iostream>
#include <ostream>
#include <string>
#include <stdexcept>

class progressbar {

public:
    // Ĭ����������
    ~progressbar() = default;

    // ɾ��������������
    progressbar(progressbar const&) = delete;
    progressbar& operator=(progressbar const&) = delete;
    progressbar(progressbar&&) = delete;
    progressbar& operator=(progressbar&&) = delete;

    // Ĭ�Ϲ��캯���������Ժ���� set_niter
    inline progressbar();
    inline progressbar(int n, bool showbar = true, std::ostream& out = std::cerr);

    // ���ý��������ٴ�ʹ��
    inline void reset();
    // ����ѭ����������
    inline void set_niter(int iter);
    // ѡ����ʽ
    inline void set_done_char(const std::string& sym) { done_char = sym; }
    inline void set_todo_char(const std::string& sym) { todo_char = sym; }
    inline void set_opening_bracket_char(const std::string& sym) { opening_bracket_char = sym; }
    inline void set_closing_bracket_char(const std::string& sym) { closing_bracket_char = sym; }
    // ����ʾ�ٷֱ�
    inline void show_bar(bool flag = true) { do_show_bar = flag; }
    // ���������
    inline void set_output_stream(const std::ostream& stream) { output.rdbuf(stream.rdbuf()); }
    // ��Ҫ����
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
        "progressbar::set_niter: ��������Ϊ�����");
    n_cycles = niter;
    return;
}

inline void progressbar::update() {

    if (n_cycles == 0) throw std::runtime_error(
        "progressbar::update: δ����ѭ������");

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

    // ����ٷֱȣ����û�б仯�������κβ���������
    perc = progress * 100. / (n_cycles - 1);
    if (perc < last_perc) return;

    // ÿ��λ���°ٷֱ�
    if (perc == last_perc + 1) {
        // ������ȷ�������ַ�
        if (perc <= 10)                output << "\b\b" << perc << '%';
        else if (perc > 10 and perc < 100) output << "\b\b\b" << perc << '%';
        else if (perc == 100)               output << "\b\b\b" << perc << '%';
    }
    if (do_show_bar == true) {
        // ÿʮ����λ���½�����
        if (perc % 2 == 0) {
            // ����������
            output << std::string(closing_bracket_char.size(), '\b');
            // ����β��ٷֱ��ַ�
            if (perc < 10)               output << "\b\b\b";
            else if (perc >= 10 && perc < 100) output << "\b\b\b\b";
            else if (perc == 100)              output << "\b\b\b\b\b";

            // ���� 'todo_char'
            for (int j = 0; j < 50 - (perc - 1) / 2; ++j) {
                output << std::string(todo_char.size(), '\b');
            }

            // ���һ������� 'done_char'
            if (perc == 0) output << todo_char;
            else           output << done_char;

            // �� 'todo_char' ���
            for (int j = 0; j < 50 - (perc - 1) / 2 - 1; ++j) output << todo_char;

            // �������β��ٷֱ��ַ�
            output << closing_bracket_char << ' ' << perc << '%';
        }
    }
    last_perc = perc;
    ++progress;
    output << std::flush;

    return;
}

#endif