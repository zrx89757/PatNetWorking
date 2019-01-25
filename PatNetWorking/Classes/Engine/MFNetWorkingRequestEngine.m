//
//  MFNetWorkRequestEngine.m
//  MFNetWork
//
//  Created by Mafeng-MacPro on 2018/11/4.
//  Copyright © 2018年 test. All rights reserved.
//

#import "MFNetWorkingRequestEngine.h"
#import "MFRequest.h"

@interface MFNetWorkingRequestEngine()
@end

@implementation MFNetWorkingRequestEngine

-(instancetype)init
{
    self = [super init];
    if (self) {
        
    }
    return self;
}

- (void)sendRequest:(NSString *)url
             method:(MFRequestMethodType)method
         parameters:(id)parameters
          loadCache:(BOOL)loadCache
      cacheDuration:(NSTimeInterval)cacheDuration
            handler:(MFRequestCompletionHandler)handler;
{
    if (url.length<=0) {
        return;
    }
    
    //request complete url
    NSString* completeUrl = url;
    if (self.manager.requestUrlFormerBlock) {
        completeUrl = self.manager.requestUrlFormerBlock (url);
    }
    
    //create request no create any request
    MFRequest* request = [self createRequest:url method:method parameters:parameters loadCache:loadCache cacheDuration:cacheDuration handler:handler];
    
    __block id param = nil;
    __block NSDictionary *headers = nil;
    if (self.manager.requestReformer && [self.manager.requestReformer respondsToSelector:@selector(requestReformerWithHeaders:parameters:finished:)]) {
        [self.manager.requestReformer requestReformerWithHeaders:nil parameters:parameters finished:^(id newHeaders, id newParameters) {
            param = newParameters;
            headers = newHeaders;
        }];
    }
    
    //add custom headers
    [self addCustomHeaders:headers];
    
    //start request flow
     [self starRequest:request completeUrl:completeUrl method:method parameters:param loadCache:loadCache cacheDuration:cacheDuration handler:handler];

}

- (void)starRequest:(MFRequest*)request
        completeUrl:(NSString*)url
             method:(MFRequestMethodType)method
         parameters:(id)parameters
          loadCache:(BOOL)loadCache
      cacheDuration:(NSTimeInterval)cacheDuration
            handler:(MFRequestCompletionHandler)handler;
{
    
    if (method == MFRequestMethodGET) {
        request.task = [self.sessionManager GET:url parameters:parameters progress:^(NSProgress * _Nonnull downloadProgress) {
        } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
            [self handleRequestResult:task responseObject:responseObject error:nil];
        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            [self handleRequestResult:task responseObject:nil error:error];
        }];
        
    }else if (method == MFRequestMethodPOST) {
        request.task = [self.sessionManager POST:url parameters:parameters progress:^(NSProgress * _Nonnull uploadProgress) {
        } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
            [self handleRequestResult:task responseObject:responseObject error:nil];
        } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
            [self handleRequestResult:task responseObject:nil  error:error];
        }];
    }
    request.identifer = [NSString stringWithFormat:@"%lu", (unsigned long)[request.task taskIdentifier]];
    
    if (self.manager.logger && [self.manager.logger respondsToSelector:@selector(printRequest:method:header:parameters:)]) {
        [self.manager.logger printRequest:request method:[self methordWithType:method] header:self.sessionManager.requestSerializer.HTTPRequestHeaders parameters:parameters];
    }
    //add request operation
    [self.manager.requestManager addRequest:request];
    [request.task resume];
}

- (void)handleRequestResult:(NSURLSessionTask *)operation
             responseObject:(id)responseObject
                      error:(NSError *)error
{
    NSString *key = [self requestHashKey:operation];
    MFRequest *request = [self getRequest:key];
      
    if (request) {
        request.error = error;
        //reform response
        if (self.manager.responseReformer && [self.manager.responseReformer respondsToSelector:@selector(responseReformer:)]) {
            request.responseObject = responseObject;
            [self.manager.responseReformer responseReformer:request];
        }
        
        //intercept
        if (self.manager.interceptor && [self.manager.interceptor respondsToSelector:@selector(interceptResponse:)]) {
            request.responseObject = responseObject;
            [self.manager.interceptor interceptResponse:request];
        }
        
        //call back block
        if (request.completionHandler) {
            request.responseObject = responseObject;
            request.completionHandler(responseObject, request, request.error);
        }
        dispatch_async(dispatch_get_main_queue(), ^{
            [self handleRequesFinished:request];
        });
    }
}

- (void)handleRequesFinished:(MFRequest*)request
{
    //print response
    if (self.manager.logger && [self.manager.logger respondsToSelector:@selector(printResponseForRequest:)]) {
        [self.manager.logger printResponseForRequest:request];
    }

    //clear all blocks
    [request clearAllBlocks];
    
    //remove this request
    [self.manager.requestManager removeRequest:request];
}

- (MFRequest*)getRequest:(NSString*)key
{
    MFRequest* request = nil;
    NSDictionary* requestInfo = self.manager.requestManager.currentRequest;
    if ([requestInfo objectForKey:key]) {
        request = requestInfo[key];
    }
    return request;
}

- (NSString *)requestHashKey:(NSURLSessionTask *)operation {
    NSString *key = [NSString stringWithFormat:@"%lu", (unsigned long)[operation taskIdentifier]];
    return key;
}

- (void)addCustomHeaders:(NSDictionary*)headers
{
    if ([headers allKeys].count>0) {
        [headers enumerateKeysAndObjectsUsingBlock:^(id key, id value, BOOL *stop) {
            if ([key isKindOfClass:[NSString class]] && [value isKindOfClass:[NSString class]]) {
                [self.sessionManager.requestSerializer setValue:value forHTTPHeaderField:key];
            }
        }];
    }
}

- (MFRequest*)createRequest:(NSString*)url
                     method:(MFRequestMethodType)method
                 parameters:(id)parameters
                  loadCache:(BOOL)loadCache
              cacheDuration:(NSTimeInterval)cacheDuration
                    handler:(MFRequestCompletionHandler)handler
{
    return [[MFRequest alloc]initRequestUrl:url method:method parameters:parameters loadCache:loadCache cacheDuration:cacheDuration handler:handler];
}

#pragma mark Private methords

- (NSString *)methordWithType:(MFRequestMethodType)methord
{
    switch (methord) {
        case MFRequestMethodGET:
            return MFRequestMethodGet;
            break;
        case MFRequestMethodPOST:
            return MFRequestMethodPost;
            break;
        case MFRequestMethodPUT:
            return MFRequestMethodPut;
            break;
        case MFRequestMethodDELETE:
            return MFRequestMethodDelete;
            break;
        case MFRequestMethodHEADER:
            return MFRequestMethodHead;
            break;
        default:
            break;
    }
    return @"unknown";
}


@end
