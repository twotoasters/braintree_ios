
#ifndef braintree_ios_VenmoTouchSettings_h // 1
#define braintree_ios_VenmoTouchSettings_h

#if __has_include("VenmoTouchSettings_gitignored.h") // 2
# include "VenmoTouchSettings_gitignored.h" // convenient place to keep private strings out of version control
#else // 2

#define BT_ENVIRONMENT @"sandbox"

#ifdef DEBUG // 3
#define BT_QA_MERCHANT_ID @"your_qa_merchant_id"
#define BT_QA_CLIENT_SIDE_ENCRYPTION_KEY @"your_qa_client_side_encryption_key"
#endif // 3

#define BT_SANDBOX_MERCHANT_ID @"your_sandbox_merchant_id"
#define BT_SANDBOX_CLIENT_SIDE_ENCRYPTION_KEY @"your_sandbox_client_side_encryption_key"

#define BT_PRODUCTION_MERCHANT_ID @"your_production_merchant_id"
#define BT_PRODUCTION_CLIENT_SIDE_ENCRYPTION_KEY @"your_production_client_side_encryption_key"

#endif  // 2
#endif  // 3
