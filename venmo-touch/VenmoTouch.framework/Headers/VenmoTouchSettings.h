//
//  VenmoTouchSettings.h
//  braintree-ios
//
//  Created by kortina on 3/28/13.
//  Copyright (c) 2013 Braintree. All rights reserved.
//

#ifndef braintree_ios_VenmoTouchSettings_h
#define braintree_ios_VenmoTouchSettings_h

#if __has_include("VenmoTouchSettings_gitignored.h") // convenient place to keep private strings out of version control
# include "VenmoTouchSettings_gitignored.h"
#else

#define BT_SANDBOX_MERCHANT_ID @"your_sandbox_merchant_id"
#define BT_SANDBOX_PUBLIC_ENCRYPTION_KEY @"your_sandbox_public_encryption_key

#define BT_PRODUCTION_MERCHANT_ID @"your_production_merchant_id"
#define BT_PRODUCTION_PUBLIC_ENCRYPTION_KEY @"your_production_public_encryption_key"

#define BT_ENVIRONMENT @"sandbox"

#endif
#endif


