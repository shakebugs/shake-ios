Pod::Spec.new do |s|
  s.name         = 'Shake'
  s.version      = '5.0.1'
  s.summary      = 'Simple, powerful bug reporting'
  s.description  = <<-DESC
Shake allows simple and powerful bug reporting. Paste 1 line of code into your app and tell testers to just shake their phone to report bugs!
                   DESC
  s.homepage     = 'http://www.shakebugs.com/'
  s.license      = { :type => 'Commercial', :file => 'LICENSE.md' }
  s.author       = { 'Shake Team' => 'team@shakebugs.com' }
  s.platform     = :ios, '8.0'
  s.source       = { :git => 'https://github.com/shakebugs/shake-ios.git', :tag => '5.0.1' }
  s.library      = 'z'
  s.requires_arc = true
  s.source_files = 'Shake.framework/Headers/*.{h}'
  s.vendored_frameworks = 'Shake.framework'
  s.preserve_paths =  'Shake.framework/*'
end