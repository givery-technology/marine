cat doc | awk '{
    if ($0 ~ "@@BEGIN_README") {
        start = 1;
    } else {
        if ($0 ~ "@@BEGIN_EN") {
            p = 1;
        } else if ($0 ~ "@@END_EN") {
            p = 0;
        } else if (p == 1 && start == 1) {
            print $0
        }
    }
}'
