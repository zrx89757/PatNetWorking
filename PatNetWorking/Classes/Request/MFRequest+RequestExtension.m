//
//  MFRequest+RequestExtension.m
//  MFNetWork
//
//  Created by Mafeng-MacPro on 2018/11/4.
//  Copyright © 2018年 test. All rights reserved.
//

#import "MFRequest+RequestExtension.h"
#import "objc/runtime.h"
#import "MFApiStatusGenerator.h"

//response key
static NSString *const kResponseKeyCurrency         = @"global_setting";
static NSString *const kResponseKeyData             = @"data";

static void *MFNetworkingApiStatus;

@implementation MFRequest (RequestExtension)

- (id)content
{
    if (isAcceptableDictionary(self.responseObject)) {
        return self.responseObject[kResponseKeyData];
    }
    return nil;
}

- (id)currency {
    if (isAcceptableDictionary(self.responseObject)) {
        return self.responseObject[kResponseKeyCurrency];
    }
    return nil;
}

-(MFApiStatus *)status
{
    id _status = objc_getAssociatedObject(self, &MFNetworkingApiStatus);
    if (!_status) {
        _status = [MFApiStatusGenerator generateApiStatusWithRequest:self];
        self.status = _status;
    }
    return _status;
}

-(void)setStatus:(MFApiStatus *)status
{
    objc_setAssociatedObject(self, &MFNetworkingApiStatus, status, OBJC_ASSOCIATION_RETAIN_NONATOMIC);
}


@end
