
struct ThreadInfo {
    int id;
    State state;
};

ThreadInfo readers_info[NUM_READERS];
ThreadInfo writers_info[NUM_WRITERS];
bool running = true;

const char* stateToString(State s) {
    switch (s) {
        case SLEEPING: return "Spi     ";
        case WAITING:  return "Czeka   "