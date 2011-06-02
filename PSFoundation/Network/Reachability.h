//
// Reachability.m
// PSFoundation
//
//  Includes code by the following:
//   - Apple Inc.         2010.  Apple Sample.
//   - Andrew Donoho.     2009.  BSD.
//   - Matthias Tretter.  2011.
//

#import <Foundation/Foundation.h>
#import <SystemConfiguration/SystemConfiguration.h>
#include <netinet/in.h>

typedef enum {
	NotReachable = 0,
	ReachableViaWiFi,
	ReachableViaWWAN
} NetworkStatus;


extern NSString* const kReachabilityChangedNotification;

@interface Reachability: NSObject {
	BOOL localWiFiRef;
@private
	SCNetworkReachabilityRef reachabilityRef;
}



// initWithReachabilityRef- designated initializer
- (Reachability *)initWithReachabilityRef:(SCNetworkReachabilityRef)ref;
- (Reachability *)initWithReachabilityRef:(SCNetworkReachabilityRef)ref isWiFi:(BOOL)wifi;

//reachabilityWithHostName- Use to check the reachability of a particular host name.
+ (Reachability*) reachabilityWithHostName: (NSString*) hostName;

//reachabilityWithAddress- Use to check the reachability of a particular IP address.
+ (Reachability*) reachabilityWithAddress: (const struct sockaddr_in*) hostAddress;

//reachabilityForInternetConnection- checks whether the default route is available.
//  Should be used by applications that do not connect to a particular host
+ (Reachability*) reachabilityForInternetConnection;

//reachabilityForLocalWiFi- checks whether a local wifi connection is available.
+ (Reachability*) reachabilityForLocalWiFi;

//Start listening for reachability notifications on the current run loop
- (BOOL) startNotifier;
- (void) stopNotifier;

- (NetworkStatus) currentReachabilityStatus;
//WWAN may be available, but not active until a connection has been established.
//WiFi may require a connection for VPN on Demand.
- (BOOL) connectionRequired;
@end

