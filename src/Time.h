#pragma once
#include <functional>

class Time {

public:

    Time(int sec = 0) : _seconds(sec) {
        for (int i = 0; i < 4; ++i) _digits[i] = -1;
        UpdateDigits();
    }

    static const int DigitsCount = 4;

    int GetSeconds() const { return _seconds; }

    const int* GetDigits() const { return _digits; }

    void AddOnTimeChanged(std::function<void(int)> handler) {
        _timeChangedHandler = handler;
    }

    void SetSeconds(int sec) {
        _seconds = (sec >= 0) ? sec : 0;
        UpdateDigits();
    }

    void AddSeconds(int sec) {
        SetSeconds(_seconds + sec);
    }

    void AddMinutes(int min) {
        AddSeconds(min * 60);
    }

private:

    int _seconds;
    int _digits[DigitsCount];
    std::function<void(int)> _timeChangedHandler;

    void UpdateDigits() {
        int minutes = _seconds / 60;
        int seconds = _seconds % 60;
        _digits[0] = (minutes > 9) ? (minutes / 10) : (minutes > 0 ? 0 : -1);
        _digits[1] = (minutes > 0) ? (minutes % 10) : -1;
        _digits[2] = (seconds > 9) ? (seconds / 10) : (seconds > 0 ? 0 : -1);
        _digits[3] = (seconds % 10);
        if (_timeChangedHandler) {
            _timeChangedHandler(_seconds);
        }
    }

};