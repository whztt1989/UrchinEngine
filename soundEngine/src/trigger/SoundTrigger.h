#ifndef ENGINE_SOUNDTRIGGER_H
#define ENGINE_SOUNDTRIGGER_H

#include "UrchinCommon.h"

#include "behavior/SoundBehavior.h"
#include "behavior/SmoothStopAction.h"

namespace urchin
{

	class SoundTrigger
	{
		public:
			enum TriggerType
			{
				MANUAL_TRIGGER,
				SHAPE_TRIGGER
			};

			enum TriggerResultValue
			{
				NO_TRIGGER,

				PLAY,
				PLAY_LOOP,
				STOP,
				SMOOTH_STOP,
				PAUSE
			};

			SoundTrigger(const SoundBehavior &);
			virtual ~SoundTrigger();

			virtual TriggerType getTriggerType() const = 0;

			virtual TriggerResultValue evaluateTrigger(const Point3<float> &) = 0;

			const SoundBehavior &getSoundBehavior() const;

		private:
			SoundBehavior soundBehavior;
	};

}

#endif
