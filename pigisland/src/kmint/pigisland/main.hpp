namespace kmint::pigisland {
    class Main {
    public:
        Main() = default;

        void start();
        void addPigs(int amount);

        static Main* getInstance();

    private:
        static Main* _instance;
       // play::stage stage_ = play::stage{{1024, 768}};

    };
}
