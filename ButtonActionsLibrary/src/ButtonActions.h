class ButtonActions {
public:
    ButtonActions(int buttonPin);
    void begin();
    void update();
    void addAction(void (*action)(), int triggerCount);

private:
    int buttonPin;
    int buttonState;
    int lastButtonState;
    int buttonPushCounter;
    struct Action {
        void (*action)();
        int triggerCount;
    };
    Action actions[10];
    int actionCount;
};