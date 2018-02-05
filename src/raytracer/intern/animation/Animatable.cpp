#include "animation/Animatable.h"
#include "util/Math.h"

using namespace std;

template<typename T>
Animatable<T>::Animatable() {}

template<typename T>
bool Animatable<T>::hasKeyframe() {
    return keys.size() > 0;
}

template<typename T>
Keyframe<T> & Animatable<T>::getKeyframe(int frame) {
    auto it = keys.find(frame);
    if (it == keys.end()) {
        throw invalid_argument("Keyframe does not exist");
    }
    return *(it->second);
}

template<typename T>
bool Animatable<T>::addKeyframe(int frame, T value) {
    auto it = keys.find(frame);
    if (it != keys.end()) {
        return false;
    }
    keys[frame] = new Keyframe<T>(frame, value);
    return true;
}

template<typename T>
bool Animatable<T>::removeKeyframe(int frame) {
    auto it = keys.find(frame);
    if (it == keys.end()) {
        return false;
    }
    delete it->second;
    keys.erase(it);
    return true;
}

template<typename T>
void Animatable<T>::set(T value) {
    this->value = value;
}

template<typename T>
void Animatable<T>::set(function<void(T &)> lambda) {
    lambda(value);
}

template<typename T>
void Animatable<T>::set(int frame, T value) {
    auto it = keys.find(frame);
    if (it == keys.end()) {
        addKeyframe(frame, value);
    }
    else {
        it->second->setValue(value);
    }
}

template<typename T>
void Animatable<T>::set(int frame, function<void(T &)> lambda) {
    auto it = keys.find(frame);
    if (it == keys.end()) {
        keys[frame] = new Keyframe<T>(frame, get(frame));
        lambda(keys[frame]->getValue());
    }
    else {
        lambda(it->second->getValue());
    }
}

template<typename T>
T Animatable<T>::get(float t) {
    if (keys.empty()) {
        return value;
    }
    else {
        
        // First check if the keyframe exists
        if (t == floor(t)) {
            auto it = keys.find(t);
            if (it != keys.end()) {
                return it->second->getValue();
            }
        }
        
        // Then
        auto lit = keys.lower_bound(t);
        if (lit == keys.begin()) {
            return value;
        }
        else {
            auto git = lit;
            lit--;
            if (git == keys.end()) {
                return lit->second->getValue();
            }
            else {
                int st = lit->second->getFrame();
                int ed = git->second->getFrame();
                T lval = lit->second->getValue();
                T rval = git->second->getValue();
                
                float sp = t - st;
                float pg = sp / (ed - st);
                
                // return lval + pg * (rval - lval);
                
                return -(rval - lval) * pg * (pg - 2) + lval;
            }
        }
    }
}

template class Animatable<int>;
template class Animatable<float>;
template class Animatable<vec2>;
template class Animatable<vec3>;
template class Animatable<vec4>;
