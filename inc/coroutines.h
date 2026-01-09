#define STEP(wait, body) Step{ [=](){ body; }, wait }

struct Step {
    std::function<void()> callback;
    double wait;
};

struct Coroutine {
    std::vector<Step> steps;
    std::vector<double> timers;
    size_t currentStep = 0;
    bool isActive = true;
};

struct CoroutineManager {
    std::vector<Coroutine> coroutines;
    std::set<std::string> startedKeys;

private:
    std::chrono::steady_clock::time_point lastTime = std::chrono::steady_clock::now();

public:
    template<typename... Steps>
    void start(const std::string& key, Steps... steps) {
        if (startedKeys.count(key)) return;
        startedKeys.insert(key);

        Coroutine co;
        co.steps = std::vector<Step>{ steps... };
        co.timers.resize(co.steps.size());
        for (size_t i = 0; i < co.steps.size(); i++)
            co.timers[i] = co.steps[i].wait;
        coroutines.push_back(co);
    }

    void update() {
        auto now = std::chrono::steady_clock::now();
        double dt = std::chrono::duration<double>(now - lastTime).count();
        lastTime = now;

        std::vector<size_t> toRemove;

        for (size_t i = 0; i < coroutines.size(); i++) {
            Coroutine& co = coroutines[i];

            if (co.currentStep >= co.steps.size()) {
                co.isActive = false;
                toRemove.push_back(i);
                continue;
            }

            Step& step = co.steps[co.currentStep];

            if (step.callback) step.callback();

            if (step.wait > 0) {
                co.timers[co.currentStep] -= dt;
                if (co.timers[co.currentStep] <= 0.0)
                    co.currentStep++;
            } else {
                co.currentStep++;
            }
        }

        for (int j = (int)toRemove.size() - 1; j >= 0; j--) {
            coroutines.erase(coroutines.begin() + toRemove[j]);
        }
    }

    bool hasActive() const { return !coroutines.empty(); }
};

// Init Coroutines
CoroutineManager Coroutines; 

// Coroutines.start("sequence1",
//     STEP(0, printf("SEQUENCE 1 - Starting.\n")),
//     STEP(3.0, printf("SEQUENCE 1 - Waited 3 seconds.\n")),
//     STEP(0, printf("SEQUENCE 1 - Continuing after wait.\n")),
//     STEP(2.0, printf("SEQUENCE 1 - Waited 2 more seconds.\n")),
//     STEP(0, printf("SEQUENCE 1 - Completed.\n"))
// );