Pod::Spec.new do |s|
  s.name         = 'Shake'
  s.version      = '15.2.0'
  s.summary      = 'Simple, powerful bug reporting'
  s.description  = <<-DESC
Shake allows simple and powerful bug reporting. Paste 1 line of code into your app and tell testers to just shake their phone to report bugs!
                   DESC
  s.homepage     = 'http://www.shakebugs.com/'
  s.license      = { :type => 'Commercial', :file => 'LICENSE.md' }
  s.author       = { 'Shake Team' => 'team@shakebugs.com' }
  s.platform     = :ios, '12.0'
  s.source       = { :git => 'https://github.com/shakebugs/shake-ios.git', :tag => '15.2.0' }
  s.weak_frameworks = 'MessageUI', 'Security', 'SystemConfiguration'
  s.libraries = 'c++', 'iconv', 'z'
  s.vendored_frameworks = 'Sources/Shake.xcframework'
end