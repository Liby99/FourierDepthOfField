#ifndef KEYFRAME_H
#define KEYFRAME_H

template <typename T>
class Keyframe {
private:
    int frame;
    T value;
public:
    Keyframe(int frame, T value);
    void setFrame(int frame);
    void setValue(T value);
    int getFrame();
    T & getValue();
    bool operator<(Keyframe<T> k);
    bool operator==(Keyframe<T> k);
};

#endif
