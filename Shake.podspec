Pod::Spec.new do |s|
  s.name         = 'Shake'
  s.version      = '14.4.0'
  s.summary      = 'Simple, powerful bug reporting'
  s.description  = <<-DESC
Shake allows simple and powerful bug reporting. Paste 1 line of code into your app and tell testers to just shake their phone to report bugs!
                   DESC
  s.homepage     = 'http://www.shakebugs.com/'
  s.license      = { :type => 'Commercial', :file => 'LICENSE.md' }
  s.author       = { 'Shake Team' => 'team@shakebugs.com' }
  s.platform     = :ios, '11.0'
  s.source       = { :git => 'https://github.com/shakebugs/shake-ios.git', :tag => '14.4.0' }
  s.library      = 'z'
  s.requires_arc = true
  s.xcconfig     =  { 'FRAMEWORK_SEARCH_PATHS' => '$(PODS_ROOT)/Shake/' }
  s.source_files = 'Sources/Shake.xcframework/**/*.{h,m,swift}'
  s.vendored_frameworks = 'Sources/Shake.xcframework'
  s.preserve_paths =  'Sources/Shake.xcframework/*'
end