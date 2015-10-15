#ifndef _DEMUX_PLANNER_H
#define _DEMUX_PLANNER_H

#include <cstdint>
#include <queue>

class demux_planner
{
    public:
        enum output_stream_t { VD1_DCH, VD2_DCH, VD_VCH, SKIP }; // FIXME get rid of SKIP
        enum state_t { STALL, ACTIONS_PENDING, DONE };
        enum packet_type_t { HEADER, TERMINATOR, VD2, UNKNOWN };
        enum unit_type_t { CSD1, CSD2, DEST, SRC, DOWN, UP, REM12, REM34, NONE };
        struct plan_item_t
        {
            const output_stream_t output_stream;
            int position;
            int end;
            unit_type_t tag;
        };

        demux_planner();
        void arm();
        state_t get_state();
        plan_item_t get_current_item();
        void consume_current_item();
        void plan_for(packet_type_t packet, long fn);
    private:
        state_t d_state;
        std::queue<plan_item_t> d_item_queue;
};

#endif
