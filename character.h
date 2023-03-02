class character
{
public:
  std::string name;
  int hp, baseSpeed, baseAttack, accuracy, stamina, defence, speed, attack, player;
  bool guarding, preparingToDodge, prepCounterAttack, isBot, actionChosen;

  void new_character(std::string newName, int newHp, int newSpeed, int newAttack, int newDefence, int newAccuracy, int newStamina, bool initGuard = false, bool initDodge = false, bool initCounterAttack = false, bool initBot = false, bool initActionChosen = false);

  bool light_attack();

  bool heavy_attack();

  bool dodge();

  void guard();

  std::string receiveCounterAttack(character attacker);

  std::string applyAction(character attacker);

  void resetTempStats();

  void increaseStamina();
};