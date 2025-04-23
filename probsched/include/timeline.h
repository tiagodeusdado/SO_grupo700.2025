#ifndef B53BF1AC_F6CE_4F3A_A6DB_E4EF469F8F1C
#define B53BF1AC_F6CE_4F3A_A6DB_E4EF469F8F1C

typedef struct {
    int process_id;
    int start;
    int end;
} TimelineEntry;

#define MAX_TIMELINE 1000
extern TimelineEntry timeline[];
extern int timeline_count;

#endif /* B53BF1AC_F6CE_4F3A_A6DB_E4EF469F8F1C */
