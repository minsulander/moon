#ifndef MOON_NODEMASK_H
#define MOON_NODEMASK_H

namespace moon {
	namespace NodeMask {
		enum NodeMasks {
			INTERACTIVE = 0x01,
			RECEIVE_SHADOW = 0x02,
			CAST_SHADOW = 0x04,
			INTERSECT = 0x08,
			
			DEFAULT = ~ (INTERACTIVE | RECEIVE_SHADOW),
			DEFAULT_DEBUG = ~ (INTERACTIVE | RECEIVE_SHADOW | CAST_SHADOW)
		};
	}
}

#endif
