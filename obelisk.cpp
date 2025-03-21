#include <iostream>
#include <string>
#include "lifelib/pattern2.h"
#include "obelisk.h"

int64_t center[2] = CENTER;
uint64_t stabs[2] = STABS;
uint64_t period[2] = PERIOD;
uint64_t maxbbox[2] = MAXBBOX;
int64_t tile[3] = TILE;

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
                    }
                } else if (pat.getcell(i, j) == 1) {
                    p += on(i+h*tile[0], j+h*tile[1]);
                }
            }
        }
    }
	int64_t bbox2[4];
	p.getrect(bbox2);
	if (symmetry == "D2-") {
		p += p.transform("flip_y", center[0], center[1]);
	} else if (symmetry == "D2|") {
		p += p.transform("flip_x", center[0], center[1]);
	} else if (symmetry == "D4+") {
		p += p.transform("flip_x", center[0], center[1]);
		p += p.transform("flip_y", center[0], center[1]);
	}
    return p;
}

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
        work.ascertain_period();
        if (work.dt != 0 and work.totalPopulation() > 0) {
            if (work.dt >= period[0]) {
                printf("#C Pattern found with period %ld\n", work.dt);
                work.write_rle(std::cout);
				std::cout << "\n";
            }
        }
    }
    return 0;
}