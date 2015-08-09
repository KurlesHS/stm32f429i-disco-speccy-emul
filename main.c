
void _exit() {

}

int main(int argc, char**argv) {

    (void)argc;
    (void)argv;
    volatile int x = 0;
    while (1) {
        x++;
    }
    return 0;
}
