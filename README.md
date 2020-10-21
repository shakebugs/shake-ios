# Shake iOS SDK

[Shake](https://www.shakebugs.com/) is a dedicated bug reporting tool for mobile apps. Whenever a tester notices a bug, they can just shake their device and report it instantly, without ever leaving your app. Each bug report comes supplemented with various data points like location, storage, OS and others. These reports all arrive to your web Dashboard, where they can be organized with tags and found quickly using search. 

## **Step 1**: Install Shake

### Cocoapods

## **Step 1**: Add Shake SDK to your Podfile
Not using CocoaPods yet? Follow their brief [installation guide](https://guides.cocoapods.org/using/getting-started.html#installation), then run `pod init` in the root of your project.  

Next, add Shake to your `Podfile`.

#### Objective-C
```objc
pod 'Shake'
```

#### Swift
```objc
use_frameworks! 
pod 'Shake'
```

Then, run the `pod install` command in your terminal.  

Since CocoaPods might not always download the latest version of an SDK when using `pod install`, it's recommended that you also run `pod update Shake` after the installation has completed, or whenever you'd like to update Shake.


### Carthage

Not using Carthage yet? Follow their brief installation guide, then create an empty Cartfile in the root of your project and you're done.  

Open your Cartfile and add this line:

```
binary "https://github.com/shakebugs/shake-ios/raw/master/Shake.json"
```

Next, open up Terminal and enter this command:

```
carthage update
```

Link Shake library.
Once carthage update is executed, you will find the Shake binary in your project folder inside:
🗂 Carthage → 🗂 Build → 🗂 iOS → Shake.framework

Open Xcode and select your project file in the left section of the screen. Under General scroll down to the Frameworks, Libraries and Embedded Content section and drag-and-drop Shake.framework there. Make sure Embed & Sign is selected.


### Manually

Visit Shake iOS SDK GitHub repo, click the green Clone button and then Download ZIP. Shake directory will be downloaded to your computer — drag-and-drop the Shake.framework folder into your project. Then select Embed & Sign for Shake.framework in Xcode General tab; Frameworks, Libraries, and Embedded content (Xcode 11, Xcode 12).

Note:
By not using a dependency manager like CocoaPods, you won't be able to use the simple pod update Shake command to always pull the latest version of Shake SDK into your app. Instead, you will have to repeat the the first step described in the above paragraph.


## **Step 2:** Grab your API keys

Visit your Shake [dashboard](https://app.shakebugs.com/documentation/ios/installing) and grab the `Client ID` and `Secret` keys.

Open your workspace and in the Project Navigator, right click on Info.plist, and Open as › Source code. Paste this but replace your-api-client-id and your-api-client-secret with the actual values you have in your workspace settings on your Shake web dashboard.

Then, right click on your `Info.plist > Open as > Source code` and paste the keys inside.

```
<?xml version="1.0" encoding="utf-8" ?>
<plist version="1.0">
  <dict>
      <key>Shake</key>
      <dict>
        <key>APIClientID</key>
        <string>your-api-client-id</string>
        <key>APIClientSecret</key>
        <string>your-api-client-secret</string>
      </dict>
  </dict>
</plist>
```

## **Step 3:** Initialize Shake SDK
#### Objective-C
In your `AppDelegate.m`:
```objc
#import "AppDelegate.h"
@import Shake;

@implementation AppDelegate
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
  [SHKShake start];
  return YES;
}
@end
```

#### Swift
```swift
import UIKit
import Shake

@UIApplicationMain
class AppDelegate: UIResponder, UIApplicationDelegate {
  func application(
    _ application: UIApplication,
    didFinishLaunchingWithOptions launchOptions: [UIApplicationLaunchOptionsKey: Any]?) -> Bool {
      Shake.start()
      return true
  }
}
```

## **Step 4:** Build and run
Select _Product > Run_ in the menu bar. This first run will automatically add your app to your [Shake Dashboard](https://app.shakebugs.com/) based on your app bundle ID.

&nbsp;
# Requirements
- iOS 10.0+

&nbsp;
# More
- Visit our official [website](https://www.shakebugs.com/).
