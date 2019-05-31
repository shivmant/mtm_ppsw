enum DetectorState {ACTIVE,INACTIVE};
enum ServoState {CALLIB, IDLE, IN_PROGRESS};

void DetectorInit(void);
enum DetectorState eReadDetector(void);
void Automat(void);
void ServoCallib(void);
void ServoInit(unsigned int uiServoFrequency);
void ServoGoTo(unsigned int uiPosition);
