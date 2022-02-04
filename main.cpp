#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <iomanip>

using HanoiStack = std::vector<int>;
using HanoiStacks = std::array<HanoiStack, 3>;

const auto N = 4;

void printStack(HanoiStacks &stacks) {
        for (int i = N - 1; i >= 0; i--) {
                for (auto stack : stacks) {
                        auto j = stack[i];
                        if (j)
                                std::cout << std::setw(2) << j;
                        else
                                std::cout << ' ';
                        std::cout << ' ';
                }
                std::cout << std::endl;
        }
}

void moveAway(HanoiStacks &stacks, int sourceIndex, int sourceLevel, int destinationIndex, int freeIndex) {
        // Determine destinationIndex zero height
        auto destinationLevel = 0;
        while (destinationLevel != N - 1 && stacks[destinationIndex][destinationLevel] != 0)
            destinationLevel++;
        // Determine freeIndex zero height
        auto freeLevel = 0;
        while (freeLevel != N - 1 && stacks[freeIndex][freeLevel] != 0)
            freeLevel++;
        // Check if there are any disks abouve sourceIndex
        if (sourceLevel != N - 1 && stacks[sourceIndex][sourceLevel + 1] != 0) {
                // If there are move them away with the destinationIndex as freeIndex (store the original height of the stack)
                moveAway(stacks, sourceIndex, sourceLevel + 1, freeIndex, destinationIndex);
                stacks[destinationIndex][destinationLevel] = stacks[sourceIndex][sourceLevel];
                stacks[sourceIndex][sourceLevel] = 0;
                printStack(stacks);
                moveAway(stacks, freeIndex, freeLevel, destinationIndex, sourceIndex);
        } else {
                stacks[destinationIndex][destinationLevel] = stacks[sourceIndex][sourceLevel];
                stacks[sourceIndex][sourceLevel] = 0;
                printStack(stacks);
        }
}

int main() {
        auto stacks = HanoiStacks();
        for (int i = 0; i < 3; i++)
                for (int j = 0; j < N; j++)
                        stacks[i].push_back(0);
        for (int i = 0; i < N; i ++ )
                stacks[0][i] = N - i;
       moveAway(stacks, 0, 0, 1, 2);
}
