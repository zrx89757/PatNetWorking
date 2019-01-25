//
//  MFApiStatusGenerator.m
//  MFNetWork
//
//  Created by patpat on 2018/11/5.
//  Copyright © 2018年 test. All rights reserved.
//

#import "MFApiStatusGenerator.h"


//response key
static NSString *const kResponseKeyMsg               = @"status";
static NSString *const kResponseKeyCode              = @"code";
static NSString *const kResponseKeyMessage           = @"message";


@implementation MFApiStatusGenerator

+ (MFApiStatus*)generateApiStatusWithRequest:(MFRequest*)request
{
    NSDictionary *responseResult = [request responseObject];
    if ([responseResult isKindOfClass:[NSDictionary class]]) {
        id status = responseResult[kResponseKeyCode];
        id msg = responseResult[kResponseKeyMsg];
        if (isAcceptableString(responseResult[kResponseKeyMessage])) {
            msg = responseResult[kResponseKeyMessage];
        }
        if ([MFApiStatusGenerator statusIsValid:status] && isAcceptableString(msg)) {
            NSString *code = [NSString stringWithFormat:@"%@",status];
            NSString *description = [NSString stringWithFormat:@"%@",msg];
            MFApiStatus *apistatus = [MFApiStatusGenerator createStatus:code description:description domain:[request.absoluteString stringByDeletingLastPathComponent]];
            return apistatus;
        }
     }
    return nil;
}

#pragma mark Private methord

+ (BOOL)statusIsValid:(id)status
{
    if (isAcceptableString(status) || isAcceptableNumber(status)) {
        return YES;
    }
    return NO;
}

+ (MFApiStatus *)createStatus:(NSString *)code
                  description:(NSString *)description
                       domain:(NSString *)domain
{
    if (!code)return nil;
    if (description.length<=0) {
        description = @"";
    }
    if (domain.length<=0) {
        domain = @"www.patpat.com";
    }
    NSDictionary *userInfo = @{NSLocalizedDescriptionKey:description};
    MFApiStatus *status = [MFApiStatus statusWithDomain:domain code:code userInfo:userInfo];
    return status;
}

@end
