#
# Be sure to run `pod lib lint musicXML.podspec' to ensure this is a
# valid spec before submitting.
#
# Any lines starting with a # are optional, but their use is encouraged
# To learn more about a Podspec see http://guides.cocoapods.org/syntax/podspec.html
#

Pod::Spec.new do |s|
  s.name             = 'musicXML'
  s.version          = '0.0.3'
  s.summary          = 'musicxml for piano to play'
  s.description      = 'draw music sheet and play sound according to musicXML'
  s.homepage         = 'https://gitlab.oneitfarm.com/SpecPods/MusicXML'
  s.license          = { :type => 'MIT', :file => 'LICENSE' }
  s.author           = { 'tanhuiya' => 'tanhui@corp-ci.com' }
  s.source           = { :git => 'git@gitlab.oneitfarm.com:SpecPods/MusicXML.git', :tag => s.version.to_s }
  s.ios.deployment_target = '8.0'
  s.source_files = 'Pod/Classes/**/*'
  s.resource_bundles = {
    'musicXML' => ['Pod/Assets/*.png','Pod/Assets/*.dls']
  }
  s.public_header_files = 'Pod/Classes/**/*.h'
  s.vendored_frameworks = 'Pod/MusicFramwork.framework'
  s.frameworks = 'UIKit', 'MapKit','AVFoundation','AudioToolbox','CoreAudio','CoreBluetooth'
  s.vendored_libraries = 'Pod/libraries/*.a'
#  s.libraries = 'fmodL_iphoneos','fmod_iphoneos','fmodL_iphonesimulator','fmod_iphonesimulator'
end
