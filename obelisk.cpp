#include <iostream>
#include <string>
#include "lifelib/pattern2.h"
#include "obelisk.h"

int64_t center[2] = CENTER;
uint64_t stabs[2] = STABS;
uint64_t period[2] = PERIOD;
uint64_t maxbbox[2] = MAXBBOX;
int64_t tile[3] = TILE;


int main() {
    apg::lifetree<uint32_t, 4> lt(100);
    apg::pattern pat(&lt, PATTERN, RULE);
    int solutions = 0;
    bool flag = false;
    while (true) {
        flag = false;
        apg::pattern work = rand_pat(&lt, pat, tile, SYMMETRY);
        for (int s = 0; s < stabs[1]; s++) {
            int64_t bbox[4] = {0, 0, 0, 0};
            work = work.advance(stabs[0]);
            work.getrect(bbox);
            if (work.totalPopulation() > MAXPOP || bbox[2] > maxbbox[0] || bbox[3] > maxbbox[1]) {
                flag = true;
                break;
            }
        }
        apg::pattern work2(work);
        if (flag) continue;
        for (long long int p = 0; p < period[1]; p++) {
            int64_t bbox[4] = {0, 0, 0, 0};
            work = work.advance(1);
            work.getrect(bbox);
            if (work.totalPopulation() > MAXPOP || bbox[2] > maxbbox[0] || bbox[3] > maxbbox[1]) {
                break;
            }
            if (work == work2 and work.totalPopulation() > 0) {
                if ((p + 1) >= period[0]) {
                    printf("#C Pattern found with period %lld\n", p + 1);
                    work.write_rle(std::cout);
					std::cout << "\n";
                }
                break;
            }
        }
    }
    return 0;
}