Pod::Spec.new do |s|

    s.name = 'NarrativeFramework'
    s.version = '2.0.0b1'
    s.platform = :ios, '9.0'
    s.license = 'MIT'
    s.homepage = 'https://git.kiozk.ru/public-projects/narrativeframework'
    s.author = { "St.Pashik" => "stpashik@gmail.com" }
    s.source = { :git => 'https://git.kiozk.ru/public-projects/narrativeframework.git', :tag => s.version }
    s.summary = 'Библиотека для представления нарративов (Stories) с возможностью кастомизации.'
    s.description = 'Библиотека для представления нарративов (Stories) с возможностью кастомизации предоставляемая для работы с сайтом Narrator' \
                    'You can customize every detail. Make Stories of your dream! :)'

    s.requires_arc = true

    s.public_header_files = "NarrativeFramework.framework/Headers/*.h"
    s.source_files = "NarrativeFramework.framework/Headers/*.h"
    s.vendored_frameworks = "NarrativeFramework.framework"
end