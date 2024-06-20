//#include "validatorfactory.h"


//QValidator* ValidatorFactory::createValidator(InputType type, QObject *parent)
//{
//    switch (type) {
//    case InputType::EMAIL:
//        return new QRegularExpressionValidator(QRegularExpression(".*@.*"), parent);
//    case InputType::PASSWORD:
//        return new QRegularExpressionValidator(QRegularExpression("(?=.*[a-z])(?=.*[A-Z])(?=.*\\d)(?=.*[@$!%*?&])[A-Za-z\\d@$!%*?&]{8,}$"), parent);
//    default:
//        return nullptr;
//    }
//}
