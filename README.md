# 2D-Cellular-Automata

## Simple C++ function to generate 2D Cellular Automata representation in one std::vector<std::vector<bool>>

## Usage

### std::vector<std::vector<bool>> cellAutom_2D ( ... )
std::vector<std::vector<bool>> cellAutom_2D (std::vector<std::vector<bool>> input, int ruleset )

Return a two dimensional boolean standard vector according to input vector representing CA first state and a 18 bit int encoded ruleset.

Example.

`std::vector<std::vector<bool>> ca = {{0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,1,1,1,1,1,1,1,1,1,1,1,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0},
                                                                                {0,0,0,0,0,0,0,0,0,0,0,0,0}};
autom.clear();
code = ofRandom(262144);
for (int i = 0;i < NUM_ITERATIONS; i++) {
    ca = cellAutom_2D(ca,code);
    autom.push_back(ca);
} `

## About Cellular Automata

<https://content.wolfram.com/uploads/sites/34/2020/07/two-dimensional-cellular-automata.pdf>

<https://www.wolframscience.com/nks/notes-5-2--numbers-of-possible-2d-cellular-automaton-rules/>

## Screenshots

![--](screenshot/Screen Shot 2020-06-25 at 15.21.38)

![--](screenshot/Screen Shot 2020-06-25 at 15.23.16)

![--](screenshot/Screen Shot 2020-06-25 at 15.21.16)



