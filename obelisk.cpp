#include <iostream>
#include <string>
#include <map>
#include <algorithm>
#include <cmath>
#include "lifelib/pattern2.h"
#include "obelisk.h"
template <typename I>
apg::pattern rand_pat(apg::lifetree_abstract<I> *lt, apg::pattern &pat, int64_t tile[3], std::string symmetry = "C1") {
    int64_t bbox[4];
    apg::pattern on(lt, "A!", RULE);
    apg::pattern p(lt, ".!", RULE);
    pat.getrect(bbox);
    for (int h = 0; h < tile[2]; h++) {
        for (int64_t i = bbox[0]; i < bbox[2] + bbox[0]; ++i) {
            for (int64_t j = bbox[1]; j < bbox[3] + bbox[1]; ++j) {
                if (pat.getcell(i, j) == 2) {
                    if ((double)(rand() % 1000000) / 1000000. < DENSITY) {
                        p += on(i+h*tile[0], j+h*tile[1]);
                        if (symmetry == "D2-") {
                            p += on(i+h*tile[0], 2*bbox[3]-j+h*tile[1]);
                        } else if (symmetry == "D2|") {
                            p += on(2*bbox[2]-i+h*tile[0], j+h*tile[1]);
                        } else if (symmetry == "D4+") {
                            p += on(i+h*tile[0], 2*bbox[3]-j+h*tile[1]);
                            p += on(2*bbox[2]-i+h*tile[0], j+h*tile[1]);
                            p += on(2*bbox[2]-i+h*tile[0], j+h*tile[1]-j+h*tile[1]);
                        }
                    }
                } else if (pat.getcell(i, j) == 1) {
                    p += on(i+h*tile[0], j+h*tile[1]);
                    if (symmetry == "D2-") {
                        p += on(i+h*tile[0], 2*bbox[3]-j+h*tile[1]);
                    } else if (symmetry == "D2|") {
                        p += on(2*bbox[2]-i+h*tile[0], j+h*tile[1]);
                    } else if (symmetry == "D4+") {
                        p += on(i+h*tile[0], 2*bbox[3]-j+h*tile[1]);
                        p += on(2*bbox[2]-i+h*tile[0], j+h*tile[1]);
                        p += on(2*bbox[2]-i+h*tile[0], j+h*tile[1]-j+h*tile[1]);
                    }
                }
            }
        }
    }
    return p;
}

int main() {
    apg::lifetree<uint32_t, 4> lt(100);
    apg::pattern pat(&lt, PATTERN, RULE);
    int solutions = 0;
    uint64_t stabs[2] = STABS;
    uint64_t period[2] = PERIOD;
    uint64_t maxbbox[2] = MAXBBOX;
    int64_t tile[3] = TILE;
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
                    printf("Pattern found with period %lld\n", p + 1);
                    work.write_rle(std::cout);
					std::cout << "\n";
                }
                break;
            }
        }
    }
    return 0;
}