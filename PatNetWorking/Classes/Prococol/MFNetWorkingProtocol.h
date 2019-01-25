//
//  MFNetWorkProtocol.h
//  MFNetWork
//
//  Created by Mafeng-MacPro on 2018/10/31.
//  Copyright © 2018年 test. All rights reserved.
//

#import <Foundation/Foundation.h>

@class MFRequest;

//拦截器:请求完成后调用，实现协议方法后，可以在方法里完成比如说对某一状态做处理。
@protocol MFResponseInterceptor <NSObject>

@optional
- (void)interceptResponse:(MFRequest *)request;

@end

//Request reformer:对请求的数据统一做refrom处理，比如做签名，添加共用参数等
@protocol MFRequestReformer <NSObject>

@optional

- (void)requestReformerWithHeaders:(id)headers
                        parameters:(id)parameters
                          finished:(void(^)(id newHeaders,id newParameters))result;

@end

//Response reformer:对返回的数据统一做refrom处理,比如对返回数据格式处理等
@protocol MFResponseReformer <NSObject>

@optional

- (void)responseReformer:(MFRequest *)request;

@end


@protocol MFNetWorkingLogger <NSObject>

@optional

/**
 打印该请求的响应

 @param request 原始请求
 */
- (void)printResponseForRequest:(MFRequest *)request;



/**
 打印请求具体内容

 @param request 原始请求
 @param method 请求方法
 @param header 请求头
 @param params 参数
 */
- (void)printRequest:(MFRequest *)request method:(NSString *)method  header:(NSDictionary *)header parameters:(id)params;

@end
