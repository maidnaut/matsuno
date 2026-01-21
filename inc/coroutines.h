#pragma once

#define repeat(wait, body) Step{ Step::Type::Repeat, [=](){ body; }, wait }
#define once(wait, body)   Step{ Step::Type::Once,   [=](){ body; }, wait }

struct Step {
    enum class Type { Repeat, Once };
    Type type;
    std::function<void()> callback;
    double wait;
    bool fired = false;
};

struct Coroutine {
    std::string key;
    std::vector<Step> steps;
    std::vector<double> timers;
    size_t currentStep = 0;
    bool paused = false;
};

struct CoroutineManager {
    std::unordered_map<std::string, Coroutine> coroutines;

    template<typename... Steps>
    void start(const std::string& key, Steps... steps) {
        // Skip if it already exists
        if (coroutines.find(key) != coroutines.end()) return;

        Coroutine co;
        co.key = key;
        co.steps = std::vector<Step>{ steps... };
        co.timers.resize(co.steps.size());
        for (size_t i = 0; i < co.steps.size(); ++i)
            co.timers[i] = co.steps[i].wait;
            
        coroutines.emplace(key, std::move(co));
    }

    void yield(const std::string& key) {
        auto _this = coroutines.find(key);
        if (_this != coroutines.end()) _this->second.paused = true;
    }

    void resume(const std::string& key) {
        auto _this = coroutines.find(key);
        if (_this != coroutines.end()) _this->second.paused = false;
    }

    bool exists(const std::string& key) const {
        auto _this = coroutines.find(key);
        if (_this == coroutines.end()) return false;
        return _this->second.currentStep < _this->second.steps.size();
    }

    int jump(const std::string& key, int stepIndex) {
        auto _this = coroutines.find(key);
        if (_this == coroutines.end()) return 0;

        if ((size_t)stepIndex <= _this->second.steps.size()) {
            return _this->second.currentStep = (size_t)stepIndex;
        } else {
            return printf("index out of range\n");
        }
    }

    void skip(const std::string& key) {
        auto _this = coroutines.find(key);
        if (_this == coroutines.end()) return;

        _this->second.currentStep = _this->second.steps.size();
    }

    void update() {
        for (auto& pair : coroutines) {
            Coroutine& co = pair.second;

            // Skip if paused or already finished
            if (co.paused || co.currentStep >= co.steps.size()) continue;

            Step& step = co.steps[co.currentStep];

            if (step.type == Step::Type::Repeat) {
                if (step.callback) step.callback();
            } else if (!step.fired) {
                if (step.callback) step.callback();
                step.fired = true;
            }

            if (step.wait > 0) {
                co.timers[co.currentStep] -= sys.dt.deltaTime;
                if (co.timers[co.currentStep] <= 0.0)
                    ++co.currentStep;
            } else {
                ++co.currentStep;
            }
        }
    }
};

CoroutineManager Coroutines;


/*

    Coroutines.start(id, callback);
        Start a coroutine, needs to be fed an id, and either repeat or once as a callback, can be chained:

        Coroutines.start(id,
            callback(x, {...}),
            callback(x, {...}),
            callback(x, {...})
        ));

    Coroutines.start(id, once(x, {...}));
        Fires the callback once, then waits. x is a time in double

    Coroutines.start(id, repeat(x, {...}));
        Similar to once(), but repeats the step each frame until the wait expires, then moves onto the next step

    Coroutines.yield(id);
        Pauses the specified coroutine until resume() is called

    Coroutines.resume(id);
        Resumes the coroutine

    Coroutines.exists(id);
        Check if a coroutine is running, returns true or false
        
        if (Coroutines.exists(id)) {...}

    Coroutines.jump(id, index);
        Jump to the specified index

    Coroutines.skip(id);
        Completely skips over the coroutine

*/