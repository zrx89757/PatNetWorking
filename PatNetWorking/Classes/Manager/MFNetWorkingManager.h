//
//  MFNetWorkManager.h
//  MFNetWork
//
//  Created by patpat on 2018/10/31.
//  Copyright © 2018年 test. All rights reserved.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import "MFNetWorkingHeader.h"
#import "MFNetWorkingProtocol.h"
#import "MFNetWorkingRequestManager.h"


typedef NSString *(^NetWorkingUrlHandler)(NSString *originUrl);

@interface MFNetWorkingManager : NSObject

/**
 url格式化
 */
@property (nonatomic, copy) NetWorkingUrlHandler    requestUrlFormerBlock;


/**
 日志打印
 */
@property (nonatomic, strong) id<MFNetWorkingLogger> logger;


/**
 正在进行中的请求管理者
 */
@property (nonatomic,strong, readonly) MFNetWorkingRequestManager* requestManager;


//request reformer:对请求的数据统一做refrom处理，比如做签名，添加共用参数等
@property (nonatomic,weak)               id<MFRequestReformer>      requestReformer;


//response reformer:对返回的数据统一做refrom处理,比如对返回数据格式处理等
@property (nonatomic,weak)               id<MFResponseReformer>     responseReformer;


//拦截器:请求完成后调用，实现协议方法后，可以在方法里完成比如说对某一状态做处理。
@property (nonatomic,weak)               id<MFResponseInterceptor>  interceptor;


/**
 *  单例模式
 *
 *  @return MFNetWorkManager实例
 */
+ (MFNetWorkingManager *)sharedInstance;



/**
 网络是否正常连接

 @return 是否正常连接
 */
+ (BOOL)isConnected;

/**
 *  This method is used to send GET request, not consider whether to write cache & not consider whether to load cache
 *
 *  @param url                 request url
 *  @param handler             handler callback
 *
 */
- (void)sendGetRequest:(NSString *)url
               handler:(MFRequestCompletionHandler)handler;

/**
 *  This method is used to send GET request, not consider whether to write cache & not consider whether to load cache
 *
 *  @param url                 request url
 *  @param parameters          parameters
 *  @param handler             handler callback
 *
 */
- (void)sendGetRequest:(NSString *)url
            parameters:(id)parameters
               handler:(MFRequestCompletionHandler)handler;


/**
 *  This method is used to send GET request,
 consider whether to load cache but not consider whether to write cache
 *
 *  @param url                 request url
 *  @param parameters          parameters
 *  @param loadCache           consider whether to load cache
 *  @param handler             handler callback
 *
 */
- (void)sendGetRequest:(NSString *)url
            parameters:(id)parameters
             loadCache:(BOOL)loadCache
               handler:(MFRequestCompletionHandler)handler;

/**
 *  This method is used to send GET request,
 consider whether to write cache but not consider whether to load cache
 *
 *  @param url                 request url
 *  @param parameters          parameters
 *  @param cacheDuration       consider whether to write cache
 *  @param handler             handler callback
 *
 */
- (void)sendGetRequest:(NSString *)url
            parameters:(id)parameters
         cacheDuration:(NSTimeInterval)cacheDuration
               handler:(MFRequestCompletionHandler)handler;

/**
 *  This method is used to send GET request,
 consider whether to load cache and consider whether to write cache
 *
 *  @param url                 request url
 *  @param parameters          parameters
 *  @param loadCache           consider whether to load cache
 *  @param cacheDuration       consider whether to write cache
 *  @param handler             handler callback
 *
 */
- (void)sendGetRequest:(NSString *)url
            parameters:(id)parameters
             loadCache:(BOOL)loadCache
         cacheDuration:(NSTimeInterval)cacheDuration
               handler:(MFRequestCompletionHandler)handler;


/**
 *  This method is used to send POST request,
 not consider whether to write cache & not consider whether to load cache
 *
 *  @param url                request url
 *  @param parameters         parameters
 *  @param handler            handler callback
 *
 */
- (void)sendPostRequest:(NSString *)url
             parameters:(id)parameters
                handler:(MFRequestCompletionHandler)handler;


/**
 *  This method is used to send POST request,
 consider whether to load cache but not consider whether to write cache
 *
 *  @param url                 request url
 *  @param parameters          parameters
 *  @param loadCache           consider whether to load cache
 *  @param handler             handler callback
 *
 */
- (void)sendPostRequest:(NSString *)url
             parameters:(id)parameters
              loadCache:(BOOL)loadCache
                handler:(MFRequestCompletionHandler)handler;

/**
 *  This method is used to send POST request,
 consider whether to write cache but not consider whether to load cache
 *
 *  @param url                 request url
 *  @param parameters          parameters
 *  @param cacheDuration       consider whether to write cache
 *  @param handler             handler callback
 *
 */
- (void)sendPostRequest:(NSString *)url
             parameters:(id)parameters
          cacheDuration:(NSTimeInterval)cacheDuration
                handler:(MFRequestCompletionHandler)handler;


/**
 *  This method is used to send POST request,
 consider whether to load cache and consider whether to write cache
 *
 *  @param url                 request url
 *  @param parameters          parameters
 *  @param loadCache           consider whether to load cache
 *  @param cacheDuration       consider whether to write cache
 *  @param handler             handler callback
 *
 */
- (void)sendPostRequest:(NSString *)url
             parameters:(id)parameters
              loadCache:(BOOL)loadCache
          cacheDuration:(NSTimeInterval)cacheDuration
                handler:(MFRequestCompletionHandler)handler;

/**
 *  This method is used to upload image
 *
 *  @param url                   request url
 *  @param parameters            parameters
 *  @param image                 UIImage object
 *  @param name                  file name
 *  @param mimeType              file type
 *  @param uploadProgressBlock   upload progress callback
 *  @param uploadSuccessBlock    uploadSuccess allback
 *  @param uploadFailureBlock    upload failure callback
 *
 */
- (void)sendUploadImageRequest:(NSString *)url
                    parameters:(id)parameters
                         image:(UIImage *)image
                          name:(NSString *)name
                      mimeType:(NSString *)mimeType
                      progress:(MFUploadProgressBlock)uploadProgressBlock
                       success:(MFUploadSuccessBlock)uploadSuccessBlock
                       failure:(MFUploadFailureBlock)uploadFailureBlock;


/**
 *  This method is used to upload image
 *
 *  @param url                   request url
 *  @param ignoreBaseUrl         consider whether to ignore configured base url
 *  @param parameters            parameters
 *  @param image                 UIImage object
 *  @param name                  file name
 *  @param mimeType              file type
 *  @param uploadProgressBlock   upload progress callback
 *  @param uploadSuccessBlock    upload success callback
 *  @param uploadFailureBlock    upload failure callback
 *
 */
- (void)sendUploadImageRequest:(NSString *)url
                 ignoreBaseUrl:(BOOL)ignoreBaseUrl
                    parameters:(id)parameters
                         image:(UIImage *)image
                          name:(NSString *)name
                      mimeType:(NSString *)mimeType
                      progress:(MFUploadProgressBlock)uploadProgressBlock
                       success:(MFUploadSuccessBlock)uploadSuccessBlock
                       failure:(MFUploadFailureBlock)uploadFailureBlock;



/**
 *  This method is used to upload images(or only one image)
 *
 *  @param url                   request url
 *  @param parameters            parameters
 *  @param images                UIImage object array
 *  @param name                  file name
 *  @param mimeType              file type
 *  @param uploadProgressBlock   upload progress callback
 *  @param uploadSuccessBlock    upload success callback
 *  @param uploadFailureBlock    upload failure callback
 *
 */
- (void)sendUploadImagesRequest:(NSString *)url
                     parameters:(id)parameters
                         images:(NSArray<UIImage *> *)images
                           name:(NSString *)name
                       mimeType:(NSString *)mimeType
                       progress:(MFUploadProgressBlock)uploadProgressBlock
                        success:(MFUploadSuccessBlock)uploadSuccessBlock
                        failure:(MFUploadFailureBlock)uploadFailureBlock;



/**
 *  This method is used to upload images(or only one image)
 *
 *  @param url                   request url
 *  @param ignoreBaseUrl         consider whether to ignore configured base url
 *  @param parameters            parameters
 *  @param images                UIImage object array
 *  @param name                  file name
 *  @param mimeType              file type
 *  @param uploadProgressBlock   upload progress callback
 *  @param uploadSuccessBlock    upload success callback
 *  @param uploadFailureBlock    upload failure callback
 *
 */
- (void)sendUploadImagesRequest:(NSString *)url
                  ignoreBaseUrl:(BOOL)ignoreBaseUrl
                     parameters:(id)parameters
                         images:(NSArray<UIImage *> *)images
                           name:(NSString *)name
                       mimeType:(NSString *)mimeType
                       progress:(MFUploadProgressBlock)uploadProgressBlock
                        success:(MFUploadSuccessBlock)uploadSuccessBlock
                        failure:(MFUploadFailureBlock)uploadFailureBlock;


/**
 *  This method is used to upload image
 *
 *  @param url                   request url
 *  @param parameters            parameters
 *  @param image                 UIImage object
 *  @param compressRatio         compress ratio of images
 *  @param name                  file name
 *  @param mimeType              file type
 *  @param uploadProgressBlock   upload progress callback
 *  @param uploadSuccessBlock    upload success callback
 *  @param uploadFailureBlock    upload failure callback
 *
 */
- (void)sendUploadImageRequest:(NSString *)url
                    parameters:(id)parameters
                         image:(UIImage *)image
                 compressRatio:(float)compressRatio
                          name:(NSString *)name
                      mimeType:(NSString *)mimeType
                      progress:(MFUploadProgressBlock)uploadProgressBlock
                       success:(MFUploadSuccessBlock)uploadSuccessBlock
                       failure:(MFUploadFailureBlock)uploadFailureBlock;


/**
 *  This method is used to upload image
 *
 *  @param url                   request url
 *  @param ignoreBaseUrl         consider whether to ignore configured base url
 *  @param parameters            parameters
 *  @param image                 UIImage object
 *  @param compressRatio         compress ratio of images
 *  @param name                  file name
 *  @param mimeType              file type
 *  @param uploadProgressBlock   upload progress callback
 *  @param uploadSuccessBlock    upload success callback
 *  @param uploadFailureBlock    upload failure callback
 *
 */
- (void)sendUploadImageRequest:(NSString *)url
                 ignoreBaseUrl:(BOOL)ignoreBaseUrl
                    parameters:(id)parameters
                         image:(UIImage *)image
                 compressRatio:(float)compressRatio
                          name:(NSString *)name
                      mimeType:(NSString *)mimeType
                      progress:(MFUploadProgressBlock)uploadProgressBlock
                       success:(MFUploadSuccessBlock)uploadSuccessBlock
                       failure:(MFUploadFailureBlock)uploadFailureBlock;

/**
 *  This method is used to upload images(or only one image)
 *
 *  @param url                   request url
 *  @param parameters            parameters
 *  @param images                UIImage object array
 *  @param compressRatio         compress ratio of images
 *  @param name                  file name
 *  @param mimeType              file type
 *  @param uploadProgressBlock   upload progress callback
 *  @param uploadSuccessBlock    upload success callback
 *  @param uploadFailureBlock    upload failure callback
 *
 */
- (void)sendUploadImagesRequest:(NSString *)url
                     parameters:(id)parameters
                         images:(NSArray<UIImage *> *)images
                  compressRatio:(float)compressRatio
                           name:(NSString *)name
                       mimeType:(NSString *)mimeType
                       progress:(MFUploadProgressBlock)uploadProgressBlock
                        success:(MFUploadSuccessBlock)uploadSuccessBlock
                        failure:(MFUploadFailureBlock)uploadFailureBlock;

/**
 *
 *  @param url                   request url
 *  @param ignoreBaseUrl         consider whether to ignore configured base url
 *  @param parameters            parameters
 *  @param images                UIImage object array
 *  @param compressRatio         compress ratio of images
 *  @param name                  file name
 *  @param mimeType              file type
 *  @param uploadProgressBlock   upload progress callback
 *  @param uploadSuccessBlock    upload success callback
 *  @param uploadFailureBlock    upload failure callback
 *
 */
- (void)sendUploadImagesRequest:(NSString *)url
                  ignoreBaseUrl:(BOOL)ignoreBaseUrl
                     parameters:(id)parameters
                         images:(NSArray<UIImage *> *)images
                  compressRatio:(float)compressRatio
                           name:(NSString *)name
                       mimeType:(NSString *)mimeType
                       progress:(MFUploadProgressBlock)uploadProgressBlock
                        success:(MFUploadSuccessBlock)uploadSuccessBlock
                        failure:(MFUploadFailureBlock)uploadFailureBlock;


/**
 *  This method is used to cancel all current requests
 */
- (void)cancelAllCurrentRequests;


@end

